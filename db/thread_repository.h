#ifndef THREAD_REPOSITORY_H
#define THREAD_REPOSITORY_H
#include<QSqlError>
#include "../models/threadmodel.h"

class ThreadRepository
{
public:
    ThreadRepository();
    void addThreadtoDb(ThreadModel& thread);
};

#endif // THREAD_REPOSITORY_H
