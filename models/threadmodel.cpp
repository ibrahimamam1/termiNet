#include "threadmodel.h"
#include"../db/thread_repository.h"

// Default constructor
ThreadModel::ThreadModel()
    : thread_id(0), title(""), content(""), created_at(""),
    author_id(0), community_id(0), parent_thread_id(0) {}

// Parameterized constructor
ThreadModel::ThreadModel(int thread_id, const std::string &title, const std::string &content, int c_count,
                         const std::string &created_at, int author_id, int community_id,
                         int parent_thread_id)
    : thread_id(thread_id), title(title), content(content), comment_count(c_count),
    created_at(created_at), author_id(author_id),
    community_id(community_id), parent_thread_id(parent_thread_id) {}

// Getter and setter implementations
int ThreadModel::getThreadId() const { return thread_id; }
void ThreadModel::setThreadId(int id) { thread_id = id; }

std::string ThreadModel::getTitle() const { return title; }
void ThreadModel::setTitle(const std::string &title) { this->title = title; }

std::string ThreadModel::getContent() const { return content; }
void ThreadModel::setContent(const std::string &content) { this->content = content; }

int ThreadModel::getCommentCount() const { return comment_count; }
void ThreadModel::setCommentCount(const int count){ this->comment_count = count;}
std::string ThreadModel::getCreatedAt() const { return created_at; }
void ThreadModel::setCreatedAt(const std::string &created_at) { this->created_at = created_at; }

int ThreadModel::getAuthorId() const { return author_id; }
std::string ThreadModel::getAuthorName() const{return ThreadRepository::getAuthorName(this->author_id);}
void ThreadModel::setAuthorId(int author_id) { this->author_id = author_id; }

int ThreadModel::getCommunityId() const { return community_id; }
void ThreadModel::setCommunityId(int community_id) { this->community_id = community_id; }

int ThreadModel::getParentThreadId() const { return parent_thread_id; }
void ThreadModel::setParentThreadId(int parent_thread_id) { this->parent_thread_id = parent_thread_id; }
