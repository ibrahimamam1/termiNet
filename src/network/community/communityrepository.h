#ifndef COMMUNITYREPOSITORY_H
#define COMMUNITYREPOSITORY_H
#include "../../models/community/communitymodel.h"
class CommunityRepository
{
public:
    CommunityRepository();
    static bool addNewCommunity(CommunityModel community);
    static QList<CommunityModel> getCommunities(const QString& filter, const QString& value);
    static QList<CommunityModel> getUserCommunities(const QString& user_id);
};

#endif // COMMUNITYREPOSITORY_H
