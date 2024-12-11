#include "communityrepository.h"
#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>
#include <QImage>
#include <QBuffer>
#include "../models/usermodel.h"
#include "category_repository.h"
#include "storage/storagerepository.h"
#include "../utils/helper/apphelper.h"

CommunityRepository::CommunityRepository() {}

bool CommunityRepository::addNewCommunity(CommunityModel community) {
    QSqlQuery q;
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction(); // Start a transaction

    // Get unique community id
    int id;
    q.prepare("select nextval('CommunitySeq');");
    if(q.exec()){
        if(q.next()) id = q.value(0).toInt();
    } else{
        qDebug() << "Failed to get community Id : "<< q.lastError();
        return false;
    }

    //Scale the icon and banner images
    QImage scaledIconImage = AppHelper::createRoundedIcon(community.getIconImage(), 50);
    QImage scaledBannerImage = community.getBannerImage().scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //Generate unique filenames for images
    QString iconFilename = QString("%1_icon_%2.png").arg(community.getName(), id);
    QString bannerFilename = QString("%1_banner_%2.png").arg(community.getName() ,id);

    // Upload the images to the storage buckets
    QByteArray iconData;
    QBuffer iconBuffer(&iconData);
    iconBuffer.open(QIODevice::WriteOnly);
    scaledIconImage.save(&iconBuffer, "PNG"); // Save as PNG

    QByteArray bannerData;
    QBuffer bannerBuffer(&bannerData);
    bannerBuffer.open(QIODevice::WriteOnly);
    scaledBannerImage.save(&bannerBuffer, "PNG"); // Save as PNG

    // Insert into iconsBucket
    q.prepare("INSERT INTO iconsBucket(filename, filedata, uploaded_by) VALUES (:filename, :filedata, :uploaded_by)");
    q.bindValue(":filename", iconFilename);
    q.bindValue(":filedata", iconData);
    q.bindValue(":uploaded_by", UserModel::getInstance()->getId());

    if(!q.exec()){
        qDebug() << "Failed to insert into iconsBucket: " << q.lastError();
        return false;
    }

    // Insert into bannersBucket
    q.prepare("INSERT INTO bannersBucket(filename, filedata, uploaded_by) VALUES (:filename, :filedata, :uploaded_by)");
    q.bindValue(":filename", bannerFilename);
    q.bindValue(":filedata", bannerData);
    q.bindValue(":uploaded_by", UserModel::getInstance()->getId());

    if(!q.exec()){
        qDebug() << "Failed to insert into bannersBucket: " << q.lastError();
        return false;
    }

    // TODO 4: Use the generated filenames as values for icon_image and banner_image in the communities insert query
    q.prepare("INSERT INTO communities(community_id, name, description, icon_image, banner_image, created_at) VALUES (:id, :name, :des, :icon, :banner, :date);");

    // Get current timestamp in UTC and convert to PostgreSQL-compatible format
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString formattedDate = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    q.bindValue(":id", id);
    q.bindValue(":name", community.getName());
    q.bindValue(":des", community.getDescription());
    q.bindValue(":icon", iconFilename);
    q.bindValue(":banner", bannerFilename);
    q.bindValue(":date", formattedDate);

    if(!q.exec()){
        qDebug() << "Failed to insert into community table : " << q.lastError();
        return false;
    }

    // Add categories to community_category joining table atomically
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

    // Add user id to users_communitites table
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
            QImage iconImage = StorageRepository::getIconImage(iconPath);
            QImage bannerImage = StorageRepository::getBannerImage(bannerPath);
            std::vector<CategoryModel>categories = CategoryRepository::getCategoriesForCommunity(id);
            comms.push_back(CommunityModel(id, name, description, iconImage, bannerImage, categories));
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
