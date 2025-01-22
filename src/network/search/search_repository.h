#ifndef SEARCH_REPOSITORY_H
#define SEARCH_REPOSITORY_H
#include <QString>
#include "../../models/thread/threadmodel.h"
#include "../../models/community/communitymodel.h"
#include "../../models/user/usermodel.h"

class SearchRepository
{
public:
    SearchRepository();
    static int searchFor(const QString& target, QList<ThreadModel>& threads, QList<CommunityModel>& comms, QList<UserModel>& users);
};

#endif // SEARCH_REPOSITORY_H
