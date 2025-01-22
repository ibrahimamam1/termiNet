#include "communityrepository.h"
#include <QDateTime>
#include <QNetworkReply>
#include <QEventLoop>
#include <QImage>
#include <QBuffer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QSqlError>
#include "../../models/user/usermodel.h"
#include "../../models/user/authenticateduser.h"
#include "../../network/category/categoryrepository.h"
#include "../api/apiclient.h"

CommunityRepository::CommunityRepository() {}

bool CommunityRepository::addNewCommunity(CommunityModel community) {
    //Convert icon to base64 strings
    QByteArray iconData;
    QBuffer iconBuffer(&iconData);
    iconBuffer.open(QIODevice::WriteOnly);
    community.getIconImage().save(&iconBuffer, "PNG");
    QString iconBase64String = iconData.toBase64();

    //Convert banner to base64 strings
    QByteArray bannerData;
    QBuffer bannerBuffer(&bannerData);
    bannerBuffer.open(QIODevice::WriteOnly);
    community.getBannerImage().save(&bannerBuffer, "PNG");
    QString bannerBase64String = bannerData.toBase64();

    QJsonObject jsonData;
    jsonData["community_name"] = community.getName();
    jsonData["community_description"] = community.getDescription();
    jsonData["icon_image"] = iconBase64String;
    jsonData["banner_image"] = bannerBase64String;
    jsonData["founder"] = AuthenticatedUser::getInstance().getId();

    //get categories
    QList<CategoryModel> categories = community.getCategories();
    QJsonArray categoriesArray;
    for (const auto& c : categories) {
        categoriesArray.append(QString::number(c.getId()));
    }
    jsonData["categories"] = categoriesArray;

    QEventLoop loop;
    ApiClient& client = ApiClient::getInstance();
    QString url = client.getCommunitiesUrl() + "new/";
    QNetworkReply *reply = client.makePostRequest(url, jsonData);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if(reply->error() == QNetworkReply::NoError){
        QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll()).object();
        if (responseJson.contains("Status") && responseJson["Status"].toString() == "Created")
            return true;
    }

    return false;
}
QList<CommunityModel> CommunityRepository::getCommunities(const QString& filter, const QString& value){

    ApiClient& client = ApiClient::getInstance();
    QString url = client.getCommunitiesUrl() + filter + "/" + value;

    QEventLoop loop;
    QNetworkReply *reply = client.makeGetRequest(url);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    QList<CommunityModel> comms;
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QJsonDocument jsonData = QJsonDocument::fromJson(data);

        if(jsonData.isArray()) {
            QJsonArray jsonArray = jsonData.array();

            for (const QJsonValue& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    QJsonObject jsonObject = jsonValue.toObject();

                    // Extract values from the JSON object
                    QString name = jsonObject["community_name"].toString();
                    QString description = jsonObject["community_description"].toString();
                    QByteArray iconImageData = QByteArray::fromBase64(jsonObject["icon_image"].toString().toUtf8());
                    QByteArray bannerImageData = QByteArray::fromBase64(jsonObject["banner_image"].toString().toUtf8());
                    QString created_at = jsonObject["created_at"].toString();
                    size_t id = static_cast<size_t>(jsonObject["community_id"].toInt());
                    size_t memberCount = static_cast<size_t>(jsonObject["member_count"].toInt());
                    qDebug() << name << " has " << memberCount << "members";

                    QImage iconImage = QImage::fromData(iconImageData, "PNG");
                    QImage bannerImage = QImage::fromData(bannerImageData, "PNG");

                    CommunityModel comm(name, description, iconImage, bannerImage, id, created_at, memberCount);
                    comm.setJoined(true);

                    comms.append(comm);
                }
            }
        } else {
            qDebug() << "JSON data is not an array.";
        }
    }else {
        qDebug() << "Network Error";
    }
    return comms;
}
QList<CommunityModel> CommunityRepository::getUserCommunities(const QString& user_id){
    return getCommunities("user_id", user_id);
}

bool CommunityRepository::addUserToCommunity(const QString& user_id, const size_t& community_id){
    ApiClient& client = ApiClient::getInstance();
    QString url = client.getCommunitiesUrl() + "users/add/" + user_id + "/" + QString::number(community_id);

    QEventLoop loop;
    QNetworkReply* reply = client.makeGetRequest(url);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();
            bool success = jsonObject["Status"].toBool();
            return success;
        }
    }
    return false;
}

bool CommunityRepository::removeUserFromCommunity(const QString& user_id, const size_t& community_id){
    ApiClient& client = ApiClient::getInstance();
    QString url = client.getCommunitiesUrl() + "users/remove/" + user_id + "/" + QString::number(community_id);

    QEventLoop loop;
    QNetworkReply* reply = client.makeGetRequest(url);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    if(reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();
            bool success = jsonObject["Status"].toBool();
            return success;
        }
    }
    return false;
}

