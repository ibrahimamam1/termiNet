#include "loginrepository.h"
#include "../../helpers/api_client/apiclient.h"
#include <QPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QEventLoop>

LoginRepository::LoginRepository() {}

bool LoginRepository::login(const QString& email, const QString& pass){
    ApiClient *apiclient = ApiClient::getInstance();
    QString loginUri = apiclient->getLoginUrl() + email + "/" + pass;
    QNetworkReply *loginReply = apiclient->makeGetRequest(loginUri);
    QPointer<QNetworkReply> safeLoginReply(loginReply);

    // Create an event loop to wait for the response
    QEventLoop loop;
    bool loginSuccessful = false;

    QObject::connect(loginReply, &QNetworkReply::finished, [&]() {

        if (safeLoginReply && safeLoginReply->error() == QNetworkReply::NoError) {
            QByteArray data = safeLoginReply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();
                if (jsonObject.contains("body")) {
                    QJsonObject body = jsonObject["body"].toObject();
                    loginSuccessful = body["Grant Access"].toBool();
                }
            } else {
                qDebug() << "Invalid response format, not a json object";
            }
        } else {
            qDebug() << "Login Error:" << safeLoginReply->errorString();
        }
        safeLoginReply->deleteLater();
        loop.quit();
    });

    // Wait for the request to complete
    loop.exec();
    return loginSuccessful;
}

