#include "communitypage.h"
#include "../widgets/thread/threadwidget.h"
#include "../styles/buttonStyles.h"

CommunityPage::CommunityPage(QWidget *parent)
    : QWidget{parent}
{

    //setup scrollable area for threads
    scrollableArea = new QScrollArea(this);
    scrollableArea->setWidgetResizable(true);

    threadContainer = new QWidget();
    threadLayout = new QVBoxLayout(threadContainer);


    scrollableArea->setWidget(threadContainer);


    //communityInfo layout(right area)
    communityInfoContainer = new QVBoxLayout();

    bannerImage = new QLabel();
    iconImage = new QLabel();
    communityName = new QLabel();
    memberCount = new QLabel();
    communityDescription = new QTextEdit();
    communityDescription->setReadOnly(true);

    // container for banner and profile info
    QWidget* bannerInfoContainer = new QWidget();
    QVBoxLayout* bannerInfoLayout = new QVBoxLayout(bannerInfoContainer);

    // horizontal layout for icon and name
    QWidget* profileInfoContainer = new QWidget();
    QHBoxLayout* profileInfoHLayout = new QHBoxLayout(profileInfoContainer);
    profileInfoHLayout->addWidget(iconImage);
    profileInfoHLayout->addWidget(communityName);
    profileInfoHLayout->addStretch();

    bannerInfoLayout->addWidget(bannerImage);
    bannerInfoLayout->addWidget(profileInfoContainer);
    bannerInfoLayout->addWidget(memberCount);


    joinBtn = new QPushButton("join");
    joinBtn->setStyleSheet(circularBtn);
    connect(joinBtn, &QPushButton::clicked, this, &CommunityPage::onJoinBtnClicked);

    communityInfoContainer->addWidget(bannerInfoContainer);
    communityInfoContainer->addWidget(communityDescription, 2);
    communityInfoContainer->addWidget(joinBtn);

    //main container
    mainContainer = new QHBoxLayout(this);
    mainContainer->addWidget(scrollableArea, 4);
    mainContainer->addLayout(communityInfoContainer,1);
}

void CommunityPage::setCommunity(const CommunityModel& comm){
    qDebug() << "Community was set to : " << comm.getName();
    community = comm;

    QPixmap bannerPixMap;
    bannerPixMap.convertFromImage(community.getBannerImage());
    bannerImage->setPixmap(bannerPixMap);

    QPixmap iconPixMap;
    iconPixMap.convertFromImage(community.getIconImage());
    iconImage->setPixmap(iconPixMap);

    communityName->setText(community.getName());
    memberCount->setText(QString::number(community.getMemberCount()));
    communityDescription->setText(community.getDescription());

    threads = ThreadRepository::loadAllThreadsFromCommunity(comm.getId());
    for(auto thread : threads){
        ThreadWidget *threadWidget = new ThreadWidget(thread, this);

        // Add the ThreadWidget to the threadsArea layout
        threadLayout->addWidget(threadWidget);
        //connect(threadWidget, &ThreadWidget::switchToCommentScreen, this, &Home::onCommentBtnClicked);
    }
    threadLayout->addStretch(1);
}
CommunityModel CommunityPage::getCommunity() const{
    return community;
}
void CommunityPage::onJoinBtnClicked() {
    qDebug() << "Yaaay time to handle joining logic";
}
