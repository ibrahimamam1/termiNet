#include "threadmodel.h"
#include"../../db/thread_repository.h"

// Default constructor
ThreadModel::ThreadModel()
    : thread_id(0), title(""), content(""), created_at(""),
    author(UserModel()), community_id(0), parent_thread_id(0) {}

// Parameterized constructor
ThreadModel::ThreadModel(int t_id, const QString &t_title, const QString &t_content, int c_count,
                         const QString &t_created_at, UserModel& t_author, int t_community_id,
                         int t_parent_thread_id)
    : thread_id(t_id), title(t_title), content(t_content), comment_count(c_count),
    created_at(t_created_at), author(t_author),
    community_id(t_community_id), parent_thread_id(t_parent_thread_id) {}

// Getter and setter implementations
int ThreadModel::getThreadId() const { return thread_id; }
void ThreadModel::setThreadId(int id) { thread_id = id; }

QString ThreadModel::getTitle() const { return title; }
void ThreadModel::setTitle(const QString &title) { this->title = title; }

QString ThreadModel::getContent() const { return content; }
void ThreadModel::setContent(const QString &content) { this->content = content; }

int ThreadModel::getCommentCount() const { return comment_count; }
void ThreadModel::setCommentCount(const int count){ this->comment_count = count;}
QString ThreadModel::getCreatedAt() const { return created_at; }
void ThreadModel::setCreatedAt(const QString &created_at) { this->created_at = created_at; }

int ThreadModel::getAuthorId() const { return author.getId(); }
QString ThreadModel::getAuthorName() const{return author.getName();}


int ThreadModel::getCommunityId() const { return community_id; }
void ThreadModel::setCommunityId(int community_id) { this->community_id = community_id; }

int ThreadModel::getParentThreadId() const { return parent_thread_id; }
void ThreadModel::setParentThreadId(int parent_thread_id) { this->parent_thread_id = parent_thread_id; }
