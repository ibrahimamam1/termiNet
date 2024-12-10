#include "communitypage.h"

CommunityPage::CommunityPage(QWidget *parent)
    : QWidget{parent}
{
    topBar = new CustomTopBar();

    //setup left navigation area
    leftAreaLayout = new QVBoxLayout();

    //setup scrollable area for threads
    scrollableArea = new QScrollArea(this);
    scrollableArea->setWidgetResizable(true);

    threadContainer = new QWidget();
    threadLayout = new QVBoxLayout(threadContainer);


    scrollableArea->setWidget(threadContainer);

    bodyLayout = new QHBoxLayout();
    bodyLayout->addLayout(leftAreaLayout, 1);
    bodyLayout->addWidget(scrollableArea, 4);
    bodyLayout->addStretch(1);

    //setup main page container
    communityPageLayout = new QVBoxLayout();
    communityPageLayout->addWidget(topBar, 1);
    communityPageLayout->addLayout(bodyLayout, 4);
}
