#include "communitypage.h"
#include "../widgets/thread/threadwidget.h"

CommunityPage::CommunityPage(QWidget *parent)
    :QWidget{parent}
{

}


CommunityModel CommunityPage::getCommunity() const{
    return community;
}
void CommunityPage::setCommunityPage(const CommunityModel& comm){
    community = comm;
    threads = comm.getThreads();

    //setup scrollable area for threads
    threadView = new ThreadView(threads);
    communityDescriptionWidget = new CommunityDescriptionWidget(community);

    //main container
    mainContainer = new QHBoxLayout(this);
    mainContainer->addWidget(threadView, 4);
    mainContainer->addWidget(communityDescriptionWidget,1);
}
void CommunityPage::clearCommunityPage(){

}

