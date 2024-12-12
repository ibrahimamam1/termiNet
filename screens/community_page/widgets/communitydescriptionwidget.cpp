#include "communitydescriptionwidget.h"
#include "../communitypage.h"
#include "../../styles/buttonStyles.h"

CommunityDescriptionWidget::CommunityDescriptionWidget(CommunityModel& community, QWidget *parent)
    : QWidget{parent}
{

    communityInfoContainer = new QVBoxLayout(this);

    bannerImage = new QLabel();
    iconImage = new QLabel();
    communityName = new QLabel();
    memberCount = new QLabel();
    communityDescription = new QTextEdit();
    communityDescription->setReadOnly(true);

    // container for banner and profile info
    QWidget* bannerInfoContainer = new QWidget();
    QVBoxLayout* bannerInfoLayout = new QVBoxLayout(bannerInfoContainer);

    QPixmap bannerPixMap;
    bannerPixMap.convertFromImage(community.getBannerImage());
    bannerImage->setPixmap(bannerPixMap);




    // horizontal layout for icon and name
    QPixmap iconPixMap;
    iconPixMap.convertFromImage(community.getIconImage());
    iconImage->setPixmap(iconPixMap);

    communityName->setText(community.getName());
    memberCount->setText(QString::number(community.getMemberCount()));
    communityDescription->setText(community.getDescription());

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
    connect(joinBtn, &QPushButton::clicked, this, &CommunityDescriptionWidget::onJoinBtnClicked);

    communityInfoContainer->addWidget(bannerInfoContainer);
    communityInfoContainer->addWidget(communityDescription, 2);
    communityInfoContainer->addWidget(joinBtn);
}

void CommunityDescriptionWidget::onJoinBtnClicked() {
    qDebug() << "Yaaay time to handle joining logic";
}
