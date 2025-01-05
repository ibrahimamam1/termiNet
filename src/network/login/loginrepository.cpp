#include "loginrepository.h"
#include "../../../helpers/api_client/apiclient.h"
#include <QPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QEventLoop>

LoginRepository::LoginRepository() {}

LoginResult LoginRepository::login(const QString& email, const QString& pass){

    //prepare login URI
    ApiClient& apiclient = ApiClient::getInstance();
    QString loginUri = apiclient.getLoginUrl() + email + "/" + pass;

    //Make login Request to server
    QPointer<QNetworkReply> safeLoginReply(apiclient.makeGetRequest(loginUri));

    //Wait for response
    QEventLoop loop;
    LoginResult loginResult;

    QObject::connect(safeLoginReply, &QNetworkReply::finished, [&]() {

        if (safeLoginReply && safeLoginReply->error() == QNetworkReply::NoError) {
            QByteArray data = safeLoginReply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();
                if (jsonObject.contains("body")) {
                    QJsonObject body = jsonObject["body"].toObject();
                    bool success = body["Grant Access"].toBool();
                    loginResult = success ? LoginResult::SUCCESS : LoginResult::FAILED;
                }
            } else {
                qDebug() << "Invalid response format, not a json object";
                loginResult = LoginResult::SERVER_ERROR;
            }
        } else {
            qDebug() << "Login Error:" << safeLoginReply->errorString();
            loginResult = LoginResult::NETWORK_ERROR;
        }
        safeLoginReply->deleteLater();
        loop.quit();
    });

    // Wait for the request to complete
    loop.exec();
    return loginResult;
}

