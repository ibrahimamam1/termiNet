#ifndef COMMUNITYREPOSITORY_H
#define COMMUNITYREPOSITORY_H
#include "../models/communitymodel.h"
class CommunityRepository
{
public:
    CommunityRepository();
    static bool addNewCommunity(CommunityModel community);
};

#endif // COMMUNITYREPOSITORY_H
