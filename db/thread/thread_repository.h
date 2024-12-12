#ifndef THREAD_REPOSITORY_H
#define THREAD_REPOSITORY_H
#include "../../models/thread/threadmodel.h"

class ThreadRepository
{
public:
    ThreadRepository();
    static void addThreadtoDb(ThreadModel& thread);
    static std::vector<ThreadModel> loadAllThreadsFromCommunity(int community_id = -1);
    static std::vector<ThreadModel> loadAllThreadsFromUser(int user_id);
    static std::vector<ThreadModel> loadAllCommentsFromDb(int thread_id);
    static int getCommentCountForThread(int thread_id);
    static ThreadModel getSingleThread(int thread_id);
    static QString getAuthorName(int auth_id);
};

#endif // THREAD_REPOSITORY_H
