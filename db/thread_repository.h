#ifndef THREAD_REPOSITORY_H
#define THREAD_REPOSITORY_H
#include<QSqlError>
#include<string>
#include<vector>
#include "../models/threadmodel.h"

class ThreadRepository
{
public:
    ThreadRepository();
    static void addThreadtoDb(ThreadModel& thread);
    static std::vector<ThreadModel> loadAllThreadsFromDb();
    static std::vector<ThreadModel> loadAllCommentsFromDb(int thread_id);
    static int getCommentCountForThread(int thread_id);
    static ThreadModel getSingleThread(int thread_id);
    static std::string getAuthorName(int auth_id);
};

#endif // THREAD_REPOSITORY_H
