#include "user_repository.h"
#include "../../../helpers/api_client/apiclient.h"
#include "../../../helpers/apphelper.h"
#include "../../models/user/authenticateduser.h"
#include <QEventLoop>
#include <QPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>

UserRepository::UserRepository() {}

UserModel UserRepository::getUser(const QString& userUri){

    QNetworkReply *userDataReply = ApiClient::getInstance().makeGetRequest(userUri);
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

                    user.setId(body["user_id"].toString());
                    user.setName(body["user_name"].toString());
                    user.setEmail(body["user_email"].toString());
                    user.setSex(body["user_sex"].toString());
                    user.setDob(body["user_dob"].toString());
                    user.setCreatedAt(body["created_at"].toString());
                    QString base64Data = body["profile_image"].toString();
                    if(base64Data != ""){
                        qDebug() << "Got Some Image from sever";
                        QByteArray imageData = QByteArray::fromBase64(base64Data.toUtf8());
                        QPixmap pixmap;
                        if (pixmap.loadFromData(imageData)) {
                            qDebug("Set User Profile Pic \n");
                            user.setProfilePic(QIcon(pixmap));
                        }
                    }

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
    QString uri = ApiClient::getInstance().getUserDataUrl() + "1/" + email;
    return getUser(uri);
}
UserModel UserRepository::getUserFromName(const QString& name){
    QString uri = ApiClient::getInstance().getUserDataUrl() + "2/" + name;
    return getUser(uri);
}
UserModel UserRepository::getUserFromId(const QString& id){
    QString uri = ApiClient::getInstance().getUserDataUrl() + "3/" + id;
    return getUser(uri);
}


//update functions

bool UserRepository::updateUser(const QString& field, const QString& new_data){
    QJsonObject jsonObject;
    QString key = AuthenticatedUser::getInstance().getId();
    jsonObject["id"] = key;
    jsonObject["field"] = field;
    jsonObject["new_data"] = new_data;

    ApiClient& api_client = ApiClient::getInstance();
    QString url = api_client.getUpdateUserDataUrl();
    QNetworkReply *reply =  api_client.makePostRequest(url, jsonObject);

    // Wait for the reply to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Check if the reply has a 200 status code
    bool success = false;
    if (reply->error() == QNetworkReply::NoError) {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 200) {
            success = true;
        }
    }

    // Clean up the reply object
    reply->deleteLater();

    return success;
}

bool UserRepository::updateUserName(const QString &newName) {
    return updateUser("user_name", newName);
}

bool UserRepository::updateUserEmail(const QString &newEmail) {
    return  updateUser("user_email", newEmail);
}

bool UserRepository::updateUserDob(const QString &newDob) {
    return updateUser("user_dob", newDob);
}

bool UserRepository::updateUserBio(const QString &newBio) {
    return updateUser("user_bio", newBio);
}

bool UserRepository::updateUserProfilePic(const QIcon &newProfilePic) {
    QPixmap pixmap = newProfilePic.pixmap(newProfilePic.availableSizes().first());
    QImage image = pixmap.toImage();

    // Convert QImage to QByteArray in PNG format
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    // Convert QByteArray to a base64 encoded string
    QString base64Image = QString::fromLatin1(byteArray.toBase64().data());
    return updateUser("profile_image", base64Image);
}

