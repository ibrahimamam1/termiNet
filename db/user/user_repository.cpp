#include "user_repository.h"
#include "../../helpers/api_client/apiclient.h"
#include <QEventLoop>
#include <QPointer>
#include <QJsonDocument>
#include <QJsonObject>

UserRepository::UserRepository() {}

UserModel UserRepository::getUser(const QString& userUri){

    QNetworkReply *userDataReply = ApiClient::getInstance()->makeGetRequest(userUri);
    QPointer<QNetworkReply> safeUserDataReply(userDataReply);

    UserModel user = UserModel();
    QEventLoop loop;
    QObject::connect(userDataReply, &QNetworkReply::finished, [&]() {
        if (safeUserDataReply && safeUserDataReply->error() == QNetworkReply::NoError) {
            QByteArray data = safeUserDataReply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();
                if (jsonObject.contains("body")) {
                    QJsonObject body = jsonObject["body"].toObject();

                    user.setId(body["user_id"].toInt());
                    user.setName(body["user_name"].toString());
                    user.setEmail(body["user_email"].toString());
                    user.setSex(body["user_sex"].toString());
                    user.setDob(body["user_dob"].toString());
                    user.setCreatedAt(body["created_at"].toString());
                }
            } else {
                qDebug() << "Invalid response format, not a json object";
            }
        } else {
            qDebug() << "User Data Error:" << safeUserDataReply->errorString();
        }

        safeUserDataReply->deleteLater();
        loop.quit();
    });
    loop.exec();
    return user;
}

UserModel UserRepository::getUserFromEmail(const QString& email){
    QString uri = ApiClient::getInstance()->getUserDataUrl() + "1/" + email;
    return getUser(uri);
}
UserModel UserRepository::getUserFromName(const QString& name){
    QString uri = ApiClient::getInstance()->getUserDataUrl() + "2/" + name;
    return getUser(uri);
}
UserModel UserRepository::getUserFromId(int id){
    QString uri = ApiClient::getInstance()->getUserDataUrl() + "3/" + QString::number(id);
    return getUser(uri);
}
