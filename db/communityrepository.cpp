#include "communityrepository.h"
#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include "../models/usermodel.h"
#include "category_repository.h"

CommunityRepository::CommunityRepository() {}

bool CommunityRepository::addNewCommunity(CommunityModel community) {
    QSqlQuery q;
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction(); // Start a transaction

    //get unique community id
    int id;
    q.prepare("select nextval('CommunitySeq');");
    if(q.exec()){
        if(q.next()) id = q.value(0).toInt();
    } else{
        qDebug() << "Failed to get community Id : "<< q.lastError();
        return false;
    }

    //insert into communities table
    q.prepare("INSERT INTO communities(community_id, name, description,icon_image, banner_image, created_at) VALUES (:id, :name, :des, :icon, :banner, :date);");

    // Get current timestamp in UTC and convert to PostgreSQL-compatible format
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString formattedDate = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    q.bindValue(":id", id);
    q.bindValue(":name", community.getName());
    q.bindValue(":des", community.getDescription());
    q.bindValue(":icon", community.getIconImage());
    q.bindValue(":banner", community.getBannerImage());
    q.bindValue(":date", formattedDate);

    if(!q.exec()){
        qDebug() << "Failed to insert into community table : " << q.lastError();
        return false;
    }

    //add categories to community_category joining table atomically

    try {
        for(auto cat : community.getCategories()){
            q.prepare("INSERT INTO community_categories(community_id, category_id) VALUES (:id, :cat_id)");
            q.bindValue(":id", id);
            q.bindValue(":cat_id", cat.getId());
            if(!q.exec()){
                throw std::runtime_error("Failed to insert category");
            }
        }
        db.commit(); // Commit the transaction if all insertions succeed
    } catch (const std::exception& e) {
        db.rollback();
        qDebug() << "Transaction failed: " << e.what();
        return false;
    }

    //add user id to users_communitites table
    q.prepare("insert into users_communities(user_id, community_id) values (:u_id, :c_id);");
    int u_id = UserModel::getInstance()->getId();
    q.bindValue(":u_id", u_id);
    q.bindValue(":c_id", id);

    if(!q.exec()){
        qDebug() << "Failed to add entry to user_community";
        return false;
    }
    return true;

}

std::vector<CommunityModel> CommunityRepository::getUserCommunities(int user_id){
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
            std::vector<CategoryModel>categories = CategoryRepository::getCategoriesForCommunity(id);
            comms.push_back(CommunityModel(id, name, description, iconPath, bannerPath, categories));
        }
    }
    return comms;
}
