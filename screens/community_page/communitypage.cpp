#include "communitypage.h"
#include "../widgets/thread/threadwidget.h"

CommunityPage::CommunityPage(CommunityModel& comm , QWidget *parent)
    :community(comm), threads(comm.getThreads()) , QWidget{parent}
{
    //setup scrollable area for threads
    threadView = new ThreadView(threads);
    communityDescriptionWidget = new CommunityDescriptionWidget(community);

    //main container
    mainContainer = new QHBoxLayout(this);
    mainContainer->addWidget(threadView, 4);
    mainContainer->addWidget(communityDescriptionWidget,1);
}


CommunityModel CommunityPage::getCommunity() const{
    return community;
}

