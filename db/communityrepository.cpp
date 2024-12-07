#include "communityrepository.h"
#include <QSqlQuery>
#include <QDateTime>

CommunityRepository::CommunityRepository() {}

bool CommunityRepository::addNewCommunity(CommunityModel community) {
    QSqlQuery q;

    //get unique community id
    int id;
    q.prepare("select nextval('CommunitySeq');");
    if(q.exec()){
        if(q.next()) id = q.value(0).toInt();
    } else{
        qDebug() << "Failed to get community Id";
        return false;
    }

    //insert into communities table
    q.prepare("INSERT INTO communities(community_id, name, description, created_at) VALUES (:id, :name, :des, :date);");

    // Get current timestamp in UTC and convert to PostgreSQL-compatible format
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    QString formattedDate = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    q.bindValue(":id", id);
    q.bindValue(":name", community.getName());
    q.bindValue(":des", community.getDescription());
    q.bindValue(":date", formattedDate);

    if(!q.exec()){
        return false;
    }

    //add categories to community_category joining table atomically
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction(); // Start a transaction

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

    return true;

}
