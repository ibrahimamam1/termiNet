#include "communitypage.h"


CommunityPage::CommunityPage(QWidget *parent)
    :QWidget{parent}
{
    isSet = false;
}


CommunityModel CommunityPage::getCommunity() const{
    return community;
}
void CommunityPage::setCommunityPage(const CommunityModel& comm){
    community = comm;
    threads = comm.getThreads();

    if(!isSet){
        isSet = true;
        threadView = new ThreadView(threads);
        communityDescriptionWidget = new CommunityDescriptionWidget(community);
        mainContainer = new QHBoxLayout(this);
        mainContainer->addWidget(threadView);
        mainContainer->addWidget(communityDescriptionWidget);
    }
    else{
        communityDescriptionWidget->setCommunity(comm);
        threadView->setThreads(threads);
    }

}

