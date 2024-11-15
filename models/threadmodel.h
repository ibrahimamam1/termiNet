#ifndef THREADMODEL_H
#define THREADMODEL_H

#include <string>

class ThreadModel
{
private:
    int thread_id;
    std::string title;
    std::string content;
    std::string created_at;
    int author_id;
    int community_id;
    int parent_thread_id;

public:
    ThreadModel();

    // Parameterized constructor
    ThreadModel(int thread_id, const std::string &title, const std::string &content,
                const std::string &created_at, int author_id, int community_id,
                int parent_thread_id);

    // Getter and setter methods
    int getThreadId() const;
    void setThreadId(int id);

    std::string getTitle() const;
    void setTitle(const std::string &title);

    std::string getContent() const;
    void setContent(const std::string &content);

    std::string getCreatedAt() const;
    void setCreatedAt(const std::string &created_at);

    int getAuthorId() const;
    void setAuthorId(int author_id);

    int getCommunityId() const;
    void setCommunityId(int community_id);

    int getParentThreadId() const;
    void setParentThreadId(int parent_thread_id);
};

#endif // THREADMODEL_H
