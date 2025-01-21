#ifndef THREAD_REPOSITORY_H
#define THREAD_REPOSITORY_H
#include "../../models/thread/threadmodel.h"

class ThreadRepository
{
public:
    ThreadRepository();
    static bool postNewThread(ThreadModel& thread);
    static QList<ThreadModel> loadAllThreads();
    static QList<ThreadModel> loadThreads(const QString& filter, const QString& value);
    static QList<ThreadModel> loadAllThreadsFromCommunity(const int& communityId );
    static QList<ThreadModel> loadAllThreadsFromUser(const QString& user_id);
    static QList<ThreadModel> loadAllThreadsFromParentThread(int parent_thread_id);
};

#endif // THREAD_REPOSITORY_H
