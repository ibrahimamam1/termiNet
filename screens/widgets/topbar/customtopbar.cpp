#include "customtopbar.h"


CustomTopBar::CustomTopBar(QWidget *parent)
    : QWidget{parent}
{
    // Header layout
    headerContainer = new QHBoxLayout(this);
    logo = new QLabel();
    logo->setPixmap(QPixmap("../../assets/logo.png"));
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search...");
    connect(searchBar, &QLineEdit::returnPressed, this, &CustomTopBar::onSearchTriggered);

    createPostIcon = new ClickableLabel(this);
    createPostIcon->setPixmap(QPixmap("../../assets/createPost.png"));
    createPostIcon->setCursor(Qt::PointingHandCursor);
    connect(createPostIcon, &ClickableLabel::clicked, this, &CustomTopBar::onCreatePostIconClicked);

    messageIcon = new ClickableLabel(this);
    messageIcon->setPixmap(QPixmap("../../assets/messageIcon.png"));
    messageIcon->setCursor(Qt::PointingHandCursor);
    messageIcon->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(messageIcon, &ClickableLabel::clicked, this, &CustomTopBar::onMessageIconClicked);

    profileIcon = new ClickableLabel(this);
    profileIcon->setPixmap(QPixmap("../../assets/profileIcon.png"));
    profileIcon->setCursor(Qt::PointingHandCursor);
    profileIcon->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(profileIcon, &QLabel::linkActivated, this, &CustomTopBar::onProfileIconClicked);

    headerContainer->addWidget(logo, 1);
    headerContainer->addWidget(searchBar, 6);
    headerContainer->addWidget(createPostIcon,1);
    headerContainer->addWidget(messageIcon, 1);
    headerContainer->addWidget(profileIcon, 1);
}

void CustomTopBar::onCreatePostIconClicked(){
    qDebug() << "Create Post Btn Clicked";
    CreatePost *createPostWidget = new CreatePost();
    createPostWidget->show();
}
void CustomTopBar::onSearchTriggered(){

}
void CustomTopBar::onMessageIconClicked(){
    qDebug() << "Message Btn Clicked";
    emit messageIconClicked();
}
void CustomTopBar::onProfileIconClicked(){
    qDebug() << "Profiles Btn Clicked";
}
