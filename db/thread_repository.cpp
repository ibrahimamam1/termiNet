#include "thread_repository.h"
#include <QSqlQuery>

ThreadRepository::ThreadRepository() {}

void ThreadRepository::addThreadtoDb(ThreadModel& thread){
    QSqlQuery q;
    int id;

    //get next thread id from sequence
    if (q.exec("SELECT NEXTVAL('THREADSEQ');")) {
        if (q.next()) {
            id = q.value(0).toInt();
        } else {
            qDebug() << "Failed to retrieve the next sequence value.";
        }
    } else {
        qDebug() << "Failed to execute the sequence query:" << q.lastError().text();
    }

    q.prepare(
        "INSERT INTO threads(thread_id, title, content, created_at, author_id, community_id, parent_thread_id)"
        "values(:thread_id, :title, :content, :created_at, :author_id, :community_id, :parent_thread_id)"
        );


    //get current time and date and convert it to a postgresql compatible type
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char created_at[11]; // YYYY-MM-DD is 10 characters + null terminator
    strftime(created_at, sizeof(created_at), "%Y-%m-%d", ltm);

    q.bindValue(":thread_id", id);
    q.bindValue(":title",  QString::fromStdString(thread.getTitle()));
    q.bindValue(":content", QString::fromStdString(thread.getContent()));
    q.bindValue(":created_at",   QString::fromStdString(created_at));
    q.bindValue(":author_id",   QString::number(thread.getAuthorId()));
    q.bindValue(":community_id",   QString::number(thread.getCommunityId()));
    q.bindValue(":parent_thread_id",   QString::number(thread.getParentThreadId()));

    if (!q.exec()) {
        qDebug() << "Insert failed:" << q.lastError().text();
    } else {
        qDebug() << "Thread Insert successful";
    }

}
std::vector<ThreadModel> ThreadRepository::loadAllThreadsFromDb() {
    std::vector<ThreadModel> threads;
    QSqlQuery q;

    if (q.exec("SELECT * FROM threads;")) {
        while (q.next()) {
            int commentCount = getCommentCountForThread(q.value(6).toInt());

            // Create ThreadModel object
            ThreadModel t(
                q.value(0).toInt(),
                q.value(1).toString().toStdString(),
                q.value(2).toString().toStdString(),
                commentCount,
                q.value(3).toString().toStdString(),
                q.value(4).toInt(),
                q.value(5).toInt(),
                q.value(6).toInt()
                );

            threads.push_back(t);
        }
    } else {
        qDebug() << "Failed to execute get threads query:" << q.lastError().text();
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
            int commentCount = getCommentCountForThread(q.value(6).toInt());

            // Create ThreadModel object
            ThreadModel t(
                q.value(0).toInt(),
                q.value(1).toString().toStdString(),
                q.value(2).toString().toStdString(),
                commentCount,
                q.value(3).toString().toStdString(),
                q.value(4).toInt(),
                q.value(5).toInt(),
                q.value(6).toInt()
                );

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
std::string ThreadRepository::getAuthorName(int auth_id){
    QSqlQuery q;
    q.prepare("Select user_name from users where user_id=:author_id");
    q.bindValue(":author_id", auth_id);

    if(q.exec()){
        if(q.next()){
            return q.value(0).toString().toStdString();
        }
    }

    qDebug() << "Failed to get the author name";
    return NULL;
}
