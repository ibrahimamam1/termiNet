#include "threadrepository.h"
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkReply>
#include <QEventLoop>
#include "../../network/user/user_repository.h"
#include "../api/apiclient.h"

ThreadRepository::ThreadRepository() {}

bool ThreadRepository::postNewThread(ThreadModel& thread){
    QJsonObject jsonData;
    jsonData["title"] = thread.getTitle();
    jsonData["content"] = thread.getContent();
    jsonData["author_id"] = thread.getAuthor().getId();
    jsonData["community_id"] = QString::number(thread.getCommunityId());
    jsonData["parent_thread_id"] = QString::number(thread.getParentThreadId());

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

QList<ThreadModel> ThreadRepository::loadThreads(const QString& filter, const QString& value) {
    qDebug() << "Thread Repo loading threads";
    ApiClient& client = ApiClient::getInstance();
    QString url = client.getThreadsUrl() + filter + "/" + value;
    QEventLoop loop;
    QNetworkReply *reply = client.makeGetRequest(url);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    QList<ThreadModel> threads;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonData = QJsonDocument::fromJson(data);

        if (jsonData.isArray()) {
            QJsonArray jsonArray = jsonData.array();

            for (const QJsonValue& jsonValue : jsonArray) {
                if (jsonValue.isObject()) {
                    QJsonObject jsonObject = jsonValue.toObject();

                    // Extract values from the JSON object
                    QString title = jsonObject["title"].toString();
                    QString content = jsonObject["content"].toString();
                    QString createdAt = jsonObject["created_at"].toString();
                    QString authorId = jsonObject["author_id"].toString();
                    size_t threadId = static_cast<size_t>(jsonObject["thread_id"].toInt());
                    size_t communityId = static_cast<size_t>(jsonObject["community_id"].toInt());
                    size_t parentThreadId = static_cast<size_t>(jsonObject["parent_thead_id"].toInt());
                    size_t commentCount = static_cast<size_t>(jsonObject["comment_count"].toInt());

                    UserModel author = UserRepository::getUserFromId(authorId);
                    ThreadModel thread(title, content, author, communityId, parentThreadId, threadId, createdAt, commentCount);

                    threads.append(thread);
                }
            }
        } else {
            qDebug() << "JSON data is not an array.";
        }
    } else {
        qDebug() << "Network error:" << reply->errorString();
    }

    reply->deleteLater();
    return threads;
}
QList<ThreadModel> ThreadRepository::loadAllThreads(){
    return loadThreads("none", "0");
}
QList<ThreadModel> ThreadRepository::loadAllThreadsFromUser(const QString& userId){
    return loadThreads("user_id", userId);
}
QList<ThreadModel> ThreadRepository::loadAllThreadsFromCommunity(const int& communityId){
    return loadThreads("community_id", QString::number(communityId));
}

QList<ThreadModel> ThreadRepository::loadAllThreadsFromParentThread(const int parent_thread_id) {
    return loadThreads("parent_thread_id", QString::number(parent_thread_id));
}

