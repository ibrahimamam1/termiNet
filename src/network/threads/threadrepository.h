#ifndef THREAD_REPOSITORY_H
#define THREAD_REPOSITORY_H
#include "../../models/thread/threadmodel.h"

class ThreadRepository
{
public:
    ThreadRepository();
    static bool postNewThread(ThreadModel& thread);
    static std::vector<ThreadModel> loadAllThreads();
    static std::vector<ThreadModel> loadThreads(const QString& filter, const QString& value);
    static std::vector<ThreadModel> loadAllThreadsFromCommunity(const int& communityId );
    static std::vector<ThreadModel> loadAllThreadsFromUser(const QString& user_id);
    static std::vector<ThreadModel> loadAllCommentsFromDb(int parent_thread_id);
    static int getCommentCountForThread(int thread_id);
    static ThreadModel getSingleThread(int thread_id);
};

#endif // THREAD_REPOSITORY_H
