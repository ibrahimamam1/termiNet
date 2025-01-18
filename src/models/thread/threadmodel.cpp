#include "threadmodel.h"

ThreadModel::ThreadModel()
    : thread_id(0), title(""), content(""), created_at(""),
    author(UserModel()), community_id(0), parent_thread_id(0) {}

// Parameterized constructor
ThreadModel::ThreadModel(
    const QString& t_title, const QString& t_content,
    const UserModel& t_author, const size_t t_community_id,
    const size_t t_id, const QString& t_created_at,
    const size_t t_parent_thread_id, const size_t c_count)
    :title(t_title), content(t_content),
    created_at(t_created_at), author(t_author),
    thread_id(t_id), community_id(t_community_id),
    parent_thread_id(t_parent_thread_id), comment_count(c_count)
{}

// Getter and setter implementations
size_t ThreadModel::getThreadId() const { return thread_id; }
void ThreadModel::setThreadId(const size_t& id) { thread_id = id; }

QString ThreadModel::getTitle() const { return title; }
void ThreadModel::setTitle(const QString& title) { this->title = title; }

QString ThreadModel::getContent() const { return content; }
void ThreadModel::setContent(const QString& content) { this->content = content; }

size_t ThreadModel::getCommentCount() const { return comment_count; }
void ThreadModel::setCommentCount(const size_t &count) { this->comment_count = count; }

QString ThreadModel::getCreatedAt() const { return created_at; }
void ThreadModel::setCreatedAt(const QString& created_at) { this->created_at = created_at; }

UserModel ThreadModel::getAuthor() const { return author; }

size_t ThreadModel::getCommunityId() const { return community_id; }
void ThreadModel::setCommunityId(const size_t& community_id) { this->community_id = community_id; }

size_t ThreadModel::getParentThreadId() const { return parent_thread_id; }
void ThreadModel::setParentThreadId(const size_t& parent_thread_id) { this->parent_thread_id = parent_thread_id; }
