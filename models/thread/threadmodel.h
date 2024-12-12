#ifndef THREADMODEL_H
#define THREADMODEL_H

#include "../user/usermodel.h"


class ThreadModel
{
private:
    int thread_id;
    QString title;
    QString content;
    int comment_count;
    QString created_at;
    UserModel author;
    int community_id;
    int parent_thread_id;

public:
    ThreadModel();
    ThreadModel(int thread_id, const QString &title, const QString &content, int c_count,
                const QString &created_at, UserModel& author, int community_id,
                int parent_thread_id);

    // Getter and setter methods
    int getThreadId() const;
    void setThreadId(int id);

    QString getTitle() const;
    void setTitle(const QString &title);

    QString getContent() const;
    void setContent(const QString &content);

    int getCommentCount() const;
    void setCommentCount(const int count);

    QString getCreatedAt() const;
    void setCreatedAt(const QString &created_at);

    int getAuthorId() const;
    QString getAuthorName() const;
    void setAuthorId(int author_id);

    int getCommunityId() const;
    void setCommunityId(int community_id);

    int getParentThreadId() const;
    void setParentThreadId(int parent_thread_id);
};

#endif // THREADMODEL_H
