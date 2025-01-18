#include "threadrepository.h"
#include <QSqlQuery>
#include <QJsonObject>
#include <QNetworkReply>
#include <QEventLoop>
#include "../../network/user/user_repository.h"
#include "../../../../helpers/api_client/apiclient.h"

ThreadRepository::ThreadRepository() {}

bool ThreadRepository::postNewThread(ThreadModel& thread){
    QJsonObject jsonData;
    jsonData["title"] = thread.getTitle();
    jsonData["content"] = thread.getContent();
    jsonData["author_id"] = thread.getAuthor().getId();
    jsonData["community_id"] = QString::number(thread.getCommunityId());
    jsonData["parent_thread_id"] = QString::number(thread.getParentThreadId());
    jsonData["created_at"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QEventLoop loop;
    ApiClient& client = ApiClient::getInstance();
    QString url = client.getPostThreadUrl();
    QNetworkReply *reply = client.makePostRequest(url, jsonData);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 200) {
            return true;
        }
    }
    return false;
}

std::vector<ThreadModel> ThreadRepository::loadAllThreadsFromCommunity(int community_id) {
    std::vector<ThreadModel> threads;
    QSqlQuery q;

    if(community_id == -1)
        q.prepare("SELECT * FROM threads;");
    else{
        q.prepare("SELECT * FROM threads where community_id = :c_id");
        q.bindValue(":c_id", community_id);
    }

    if (!q.exec()) {
        qDebug() << "Failed to get threads";
        return threads;
    }
    while (q.next()) {
        int commentCount = getCommentCountForThread(q.value(0).toInt());
        UserModel author = UserRepository::getUserFromId(q.value(4).toString());

        // Create ThreadModel object
        ThreadModel t;

        threads.push_back(t);
    }
    return threads;
}

std::vector<ThreadModel> ThreadRepository::loadAllCommentsFromDb(int thread_id) {
    QSqlQuery q;
    q.prepare("SELECT * FROM threads where parent_thread_id = :parent_id");
    q.bindValue(":parent_id", thread_id);

    std::vector<ThreadModel> threads;
    if (q.exec()) {
        while (q.next()) {
            int commentCount = getCommentCountForThread(q.value(0).toInt());
            UserModel author = UserRepository::getUserFromId(q.value(4).toString());
            // Create ThreadModel object
            ThreadModel t;

            threads.push_back(t);
        }
    } else {
        qDebug() << "Failed to execute get threads query:" << q.lastError().text();
    }

    return threads;
}

int ThreadRepository::getCommentCountForThread(int thread_id){
    QSqlQuery q;
    int commentCount = 0;

    q.prepare("SELECT COUNT(*) FROM threads WHERE parent_thread_id = :parent");
    q.bindValue(":parent", thread_id);

    if (q.exec()) {
        if (q.next()) {
            commentCount = q.value(0).toInt();
        } else {
            qDebug() << "Failed to fetch COUNT result for parent_id:" << q.value(6).toInt();
        }
    } else {
        qDebug() << "Failed to execute COUNT query:" << q.lastError().text();
    }

    return commentCount;
}
ThreadModel ThreadRepository::getSingleThread(int thread_id){
    QSqlQuery q;
    q.prepare("SELECT * from threads where thread_id = :thread_id");
    q.bindValue(":thread_id", thread_id);

    if(!q.exec()){
        qDebug() << "Failed to load thread " << q.lastError();
        return ThreadModel();
    }
    if(!q.next()){
        qDebug() << "Empty Row : Thread doers not exist";
        return ThreadModel();
    }

    UserModel author = UserRepository::getUserFromId(q.value(4).toString());
    ThreadModel thread;
    return thread;

}

QString ThreadRepository::getAuthorName(int auth_id){
    QSqlQuery q;
    q.prepare("Select user_name from users where user_id=:author_id");
    q.bindValue(":author_id", auth_id);

    if(q.exec()){
        if(q.next()){
            return q.value(0).toString();
        }
    }

    qDebug() << "Failed to get the author name";
    return NULL;
}
