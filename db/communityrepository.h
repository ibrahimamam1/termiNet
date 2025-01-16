#ifndef COMMUNITYREPOSITORY_H
#define COMMUNITYREPOSITORY_H
#include "../models/community/communitymodel.h"
class CommunityRepository
{
public:
    CommunityRepository();
    static bool addNewCommunity(CommunityModel community);
    static std::vector<CommunityModel> getUserCommunities(const QString& user_id);
    static int getMemberCount(int comm_id);
};

#endif // COMMUNITYREPOSITORY_H
