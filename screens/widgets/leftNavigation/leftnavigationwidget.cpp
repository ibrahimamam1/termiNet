#include "leftnavigationwidget.h"
#include "../../create_community/createcommunity.h"
#include "../../home/home.h"

LeftNavigationWidget::LeftNavigationWidget(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);

    //home navigation
    homeNav = new QVBoxLayout();
    home = new QLabel();
    home->setText("<a href='#'>Home</a>");
    popular = new QLabel();
    popular->setText("<a href='#'>Popular</a>");
    discover = new QLabel();
    discover->setText("<a href='#'>Discover</a>");
    homeNav->addWidget(home, 1);
    homeNav->addWidget(popular, 1);
    homeNav->addWidget(discover, 1);

    // Community navigation
    communityNav = new QVBoxLayout();
    community = new QLabel("Communities");
    createCommunity = new QLabel();
    createCommunity->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Create Community</a>");
    createCommunity->setTextFormat(Qt::RichText);
    createCommunity->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(createCommunity, &QLabel::linkActivated, this, &LeftNavigationWidget::onCreateCommunityBtnClicked);

    communityNav->addWidget(community);
    communityNav->addWidget(createCommunity);
    getUserCommunities(communityNav);
    communityNav->addStretch();

    communityScrollArea = new QScrollArea(this);
    communityContent = new QWidget(this);
    communityContent->setLayout(communityNav);
    communityScrollArea->setWidget(communityContent);
    communityScrollArea->setWidgetResizable(true);

    mainLayout->addLayout(homeNav, 2);
    mainLayout->addWidget(communityScrollArea, 8);
}

void LeftNavigationWidget::getUserCommunities(QVBoxLayout* layout){
    userCommunities = CommunityRepository::getUserCommunities(AuthenticatedUser::getInstance()->getId());

    //create a label for every community
    for(auto comm : userCommunities){
        qDebug() << "Creating widget for " << comm.getName();
        QLabel *commLabel = new QLabel();
        QString labelText = "<a href='#'>" + comm.getName() + "</a>";
        commLabel->setText(labelText);
        commLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
        connect(commLabel, &QLabel::linkActivated, this, [this, comm]() {
            onCommunityLabelClicked(comm);
        });
        layout->addWidget(commLabel);
    }
}

void LeftNavigationWidget::onCreateCommunityBtnClicked(){
    CreateCommunity *createCommunityWidget = new CreateCommunity();
    createCommunityWidget->show();
}

void LeftNavigationWidget::onCommunityLabelClicked(CommunityModel community){
    qDebug() << "Okay let's switch to community page for" << community.getName();
    Home* home = Home::getInstance();

    home->communityPage->clearCommunityPage();
    home->communityPage->setCommunityPage(community);
    home->centerArea->setCurrentIndex(1);

}
