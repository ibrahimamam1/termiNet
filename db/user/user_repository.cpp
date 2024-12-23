#include "user_repository.h"
#include "../../helpers/api_client/apiclient.h"
#include <QEventLoop>
#include <QPointer>
#include <QJsonDocument>
#include <QJsonObject>

UserRepository::UserRepository() {}
bool UserRepository::addUserToDb(std::string name, std::string email, std::string sex, char* dob, std::string passwd, char* created_at){
    QSqlQuery q;
    int id; //generate a unique id using a stored sequence in database
    if (q.exec("SELECT NEXTVAL('IDSEQ');")) {
        if (q.next()) {
            id = q.value(0).toInt();
        } else {
            qDebug() << "Failed to retrieve the next sequence value.";
            return false;
        }
    } else {
        qDebug() << "Failed to execute the sequence query:" << q.lastError().text();
        return false;
    }

    q.prepare(
        "INSERT into users(user_id, user_name, user_email, user_sex, user_dob, user_bio, passwd, created_at)"
        "values(:user_id, :user_name, :user_email, :user_sex, :user_dob, :user_bio, :passwd, :created_at)"
        );

    q.bindValue(":user_id", id);
    q.bindValue(":user_name",  QString::fromStdString(name));
    q.bindValue(":user_email", QString::fromStdString(email));
    q.bindValue(":user_sex",   QString::fromStdString(sex));
    q.bindValue(":user_dob",   QString::fromStdString(dob));
    q.bindValue(":user_bio",   QString::fromStdString(" "));
    q.bindValue(":passwd",   QString::fromStdString(passwd));
    q.bindValue(":created_at", QString::fromStdString(created_at));

    if (!q.exec()) {
        qDebug() << "Insert failed:" << q.lastError().text();
        return false;
    }
    qDebug() << "Insert successful";
    return true;


}

void UserRepository::readUserFromDb(){
    QSqlQuery query;

    // Execute the SELECT query
    if (query.exec("SELECT user_id, user_name, user_email, user_sex, user_dob, created_at FROM users")) {
        // Iterate over each row in the result set
        while (query.next()) {
            int userId = query.value("user_id").toInt();
            QString userName = query.value("user_name").toString();
            QString userEmail = query.value("user_email").toString();
            QString userSex = query.value("user_sex").toString();
            QString userDob = query.value("user_dob").toString();
            QString createdAt = query.value("created_at").toString();

            // Print the user details
            qDebug() << "User ID:" << userId
                     << "Name:" << userName
                     << "Email:" << userEmail
                     << "Sex:" << userSex
                     << "DOB:" << userDob
                     << "Created At:" << createdAt;
        }
    } else {
        // Print error if the query execution fails
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
}

UserModel UserRepository::getUserFromId(int id){
    QSqlQuery q;
    q.prepare("select * from users where user_id = :uid");
    q.bindValue(":uid", id);

    if(!q.exec()){
        qDebug() << "Failed to retreive User";
        return UserModel();
    }
    if(!q.next()){
        qDebug() << "empty Row. User do not exist";
        return UserModel();
    }
    return UserModel();
}

UserModel UserRepository::getUserFromEmail(QString email){

    QString userUri = ApiClient::getInstance()->getUserDataUrl() + email;
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

UserModel UserRepository::getUserFromName(QString name){
    ApiClient* apiClient = ApiClient::getInstance();
    QString url = apiClient->getUserDataUrl() + name + "/";

    QNetworkReply *reply = apiClient->makeGetRequest(url);
    //connect(reply, &QNetworkReply::finished, [](){});
}
