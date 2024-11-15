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
