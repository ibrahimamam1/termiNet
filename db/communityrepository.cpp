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
#include "../src/models/user/usermodel.h"
#include "../src/models/user/authenticateduser.h"
#include "../src/network/category/categoryrepository.h"
#include "storage/storagerepository.h"
#include "../utils/helper/apphelper.h"
#include "../helpers/api_client/apiclient.h"

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

std::vector<CommunityModel> CommunityRepository::getUserCommunities(const QString& user_id){
    QSqlQuery q;
    std::vector<CommunityModel> comms;

    qDebug() << "Attempting to get Communities for "<< user_id;

    q.prepare("select * from users_communities where user_id = :uid;");
    q.bindValue(":uid", user_id);

    if(!q.exec()){
        qDebug() << "Failed to retreive info from users_communities";
        return comms;
    }
    while(q.next()){
        int comm_id = q.value(1).toInt();
        qDebug() << "Found comm id : " << comm_id;

        QSqlQuery getCommName;
        getCommName.prepare("select * from communities where community_id=:c_id");
        getCommName.bindValue(":c_id", comm_id);
        if(!getCommName.exec()){
            qDebug() << "Failed to get Community info : " << getCommName.lastError();
            return comms;
        }
        if(getCommName.next()){
            int id = getCommName.value(0).toInt();
            QString name = getCommName.value(1).toString();
            QString description = getCommName.value(2).toString();
            QString iconPath = getCommName.value(3).toString();
            QString bannerPath = getCommName.value(4).toString();
            QImage iconImage = StorageRepository::getIconImage(iconPath);
            QImage bannerImage = StorageRepository::getBannerImage(bannerPath);
            QList<CategoryModel>categories = CategoryRepository::getCategoriesForCommunity(id);
            comms.push_back(CommunityModel(name, description, iconImage, bannerImage, categories, id));
        }
    }
    return comms;
}

int CommunityRepository::getMemberCount(int comm_id){
    QSqlQuery q;
    q.prepare("select count(*) from users_communities where community_id = :c_id");
    q.bindValue(":c_id", comm_id);

    if(!q.exec()){
        qDebug() << "Failed to get member Count" << q.lastError();
        return 0;
    }
    if(!q.next()){
        qDebug() << "Empty row, community has no member";
        return 0;
    }
    return q.value(0).toInt();
}
