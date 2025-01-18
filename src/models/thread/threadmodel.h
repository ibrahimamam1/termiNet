#ifndef THREADMODEL_H
#define THREADMODEL_H

#include "../../models/user/usermodel.h"
#include <QDateTime>


class ThreadModel
{
private:
    QString title;
    QString content;
    QString created_at;
    UserModel author;
    size_t thread_id;
    size_t community_id;
    size_t parent_thread_id;
    size_t comment_count;

public:
    ThreadModel();
    ThreadModel(const QString &title, const QString &content,
                const UserModel& author, const size_t community_id = 0,
                const size_t thread_id = 0, const QString &created_at = QDateTime::currentDateTime().toString(Qt::ISODate),
                const size_t parent_thread_id = 0, const size_t c_count = 0);

    // Getter and setter methods
    size_t getThreadId() const;
    void setThreadId(const size_t& id);

    QString getTitle() const;
    void setTitle(const QString& title);

    QString getContent() const;
    void setContent(const QString& content);

    size_t getCommentCount() const;
    void setCommentCount(const size_t& count);

    QString getCreatedAt() const;
    void setCreatedAt(const QString& created_at);

    UserModel getAuthor() const;
    void setAuthor(const UserModel& author_id);

    size_t getCommunityId() const;
    void setCommunityId(const size_t& community_id);

    size_t getParentThreadId() const;
    void setParentThreadId(const size_t& parent_thread_id);
};

#endif // THREADMODEL_H
