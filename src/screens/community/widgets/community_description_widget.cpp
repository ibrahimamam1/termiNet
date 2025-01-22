#include "community_description_widget.h"
#include "../communitypage.h"
#include "../../../network/community/communityrepository.h"
#include "../../../common/style/styles.h"
#include "../../../models/user/authenticateduser.h"
#include <QFont>
#include <QFontDatabase>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

CommunityDescriptionWidget::CommunityDescriptionWidget(CommunityModel& comm, QWidget *parent)
    : QWidget{parent}
{
    community = comm;
    // Main layout
    communityInfoContainer = new QVBoxLayout(this);
    communityInfoContainer->setSpacing(10); // Add spacing between widgets
    communityInfoContainer->setContentsMargins(10, 10, 10, 10); // Add margins

    // Banner image
    bannerImage = new QLabel();
    bannerImage->setAlignment(Qt::AlignCenter);
    bannerImage->setStyleSheet("border-radius: 10px;");

    QPixmap bannerPixMap;
    bannerPixMap.convertFromImage(community.getBannerImage());
    bannerImage->setPixmap(bannerPixMap.scaled(800, 200, Qt::KeepAspectRatioByExpanding));

    // Profile info container (icon, name, and member count)
    QWidget* profileInfoContainer = new QWidget();
    QHBoxLayout* profileInfoLayout = new QHBoxLayout(profileInfoContainer);
    profileInfoLayout->setSpacing(15); // Spacing between icon and text
    profileInfoLayout->setContentsMargins(0, 0, 0, 0);

    // Community icon
    iconImage = new QLabel();
    iconImage->setFixedSize(64, 64); // Set a fixed size for the icon
    iconImage->setStyleSheet("border-radius: 32px; border: 2px solid #ffffff;");

    QPixmap iconPixMap;
    iconPixMap.convertFromImage(community.getIconImage());
    iconImage->setPixmap(iconPixMap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Community name and member count
    QWidget* textInfoContainer = new QWidget();
    QVBoxLayout* textInfoLayout = new QVBoxLayout(textInfoContainer);
    textInfoLayout->setSpacing(5);
    textInfoLayout->setContentsMargins(0, 0, 0, 0);

    communityName = new QLabel(community.getName());
    communityName->setStyleSheet("font-size: 24px; font-weight: bold; color: #333333;");

    memberCount = new QLabel(QString::number(community.getMemberCount()) + " Members");
    memberCount->setStyleSheet("font-size: 14px; color: #666666;");

    textInfoLayout->addWidget(communityName);
    textInfoLayout->addWidget(memberCount);

    // Add icon and text to profile info container
    profileInfoLayout->addWidget(iconImage);
    profileInfoLayout->addWidget(textInfoContainer);
    profileInfoLayout->addStretch(); // Push everything to the left

    // Community description
    communityDescription = new QTextEdit();
    communityDescription->setReadOnly(true);
    communityDescription->setStyleSheet(
        "font-size: 16px; color: #444444; background-color: transparent; border: none; padding: 10px;"
        );
    communityDescription->setText(community.getDescription());

    // Join button
    joinBtn = new QPushButton("");
    if(community.getJoined() == true)
        joinBtn->setText("Leave");
    else
       joinBtn->setText("Join");

    joinBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #0079D3;"
        "   color: white;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 10px 20px;"
        "   border-radius: 5px;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0066B3;"
        "}"
        );
    joinBtn->setCursor(Qt::PointingHandCursor);
    connect(joinBtn, &QPushButton::clicked, this, &CommunityDescriptionWidget::onJoinBtnClicked);

    // Add widgets to the main layout
    communityInfoContainer->addWidget(bannerImage);
    communityInfoContainer->addWidget(profileInfoContainer);
    communityInfoContainer->addWidget(communityDescription);
    communityInfoContainer->addWidget(joinBtn, 0, Qt::AlignCenter); // Center the button
}

void CommunityDescriptionWidget::onJoinBtnClicked() {
    if(community.getJoined() == false){
        bool success = CommunityRepository::addUserToCommunity(AuthenticatedUser::getInstance().getId(), community.getId());
        if(success){
            joinBtn->setText("Leave");
            community.setJoined(true);
        }
    }else{
        bool success = CommunityRepository::removeUserFromCommunity(AuthenticatedUser::getInstance().getId(), community.getId());
        if(success){
            joinBtn->setText("Join");
            community.setJoined(false);
        }
    }

}
void CommunityDescriptionWidget::setCommunity(const CommunityModel& comm){
    community = comm;
    QPixmap bannerPixMap;
    bannerPixMap.convertFromImage(comm.getBannerImage());
    bannerImage->setPixmap(bannerPixMap.scaled(800, 200, Qt::KeepAspectRatioByExpanding));

    QPixmap iconPixMap;
    iconPixMap.convertFromImage(comm.getIconImage());
    iconImage->setPixmap(iconPixMap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    communityName->setText(comm.getName());
    communityDescription->setText(comm.getDescription());
    memberCount->setText(QString::number(comm.getMemberCount()) + " members");
}
