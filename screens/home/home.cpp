#include "home.h"
#include<QTextBrowser>

Home::Home(QWidget *parent) : QMainWindow(parent), user(UserModel::getInstance())
{
    // Create a central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout
    mainContainer = new QVBoxLayout(centralWidget);

    // Header layout
    headerContainer = new QHBoxLayout();
    logo = new QLabel("Logo", this);
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search...");
    connect(searchBar, &QLineEdit::returnPressed, this, &Home::on_search_triggered);

    createPostIcon = new QLabel("Create", this);
    createPostIcon->setCursor(Qt::PointingHandCursor);
    createPostIcon->setTextFormat(Qt::RichText);
    createPostIcon->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(createPostIcon, &QLabel::linkActivated, this, &Home::on_create_post_icon_clicked);

    messageIcon = new QLabel("Messages", this);
    messageIcon->setCursor(Qt::PointingHandCursor);
    messageIcon->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(messageIcon, &QLabel::linkActivated, this, &Home::on_message_icon_clicked);

    profileIcon = new QLabel("Profile", this);
    profileIcon->setCursor(Qt::PointingHandCursor);
    profileIcon->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(profileIcon, &QLabel::linkActivated, this, &Home::on_profile_icon_clicked);

    headerContainer->addWidget(logo, 1);
    headerContainer->addWidget(searchBar, 6);
    headerContainer->addWidget(createPostIcon,1);
    headerContainer->addWidget(messageIcon, 1);
    headerContainer->addWidget(profileIcon, 1);

    // Left area layout
    leftArea = new QVBoxLayout();
    homeNav = new QVBoxLayout();
    homeNavHome = new QLabel("Home", this);
    homeNavPopular = new QLabel("Popular", this);
    homeNavDiscover = new QLabel("Discover", this);
    homeNav->addWidget(homeNavHome, 1);
    homeNav->addWidget(homeNavPopular, 1);
    homeNav->addWidget(homeNavDiscover, 1);

    // Community navigation
    communityNav = new QVBoxLayout();
    QLabel* communityLabel = new QLabel("Communities", this);
    communityNav->addWidget(communityLabel);

    QScrollArea* communityScrollArea = new QScrollArea(this);
    QWidget* communityContent = new QWidget(this);
    communityContent->setLayout(communityNav);
    communityScrollArea->setWidget(communityContent);
    communityScrollArea->setWidgetResizable(true);

    leftArea->addLayout(homeNav, 2);
    leftArea->addWidget(communityScrollArea, 8);

    // Center area layout
    centerArea = new QVBoxLayout(); // Threads will be dynamically added here.

    // Right area layout
    rightArea = new QVBoxLayout();
    createPostWidget = new CreatePost();
    currentRightWidget = new QLabel("Right Widget Placeholder", this); // Replace dynamically as needed.
    rightArea->addWidget(currentRightWidget);

    // Body layout
    bodyContainer = new QHBoxLayout();
    bodyContainer->addLayout(leftArea, 2);
    bodyContainer->addLayout(centerArea, 6);
    bodyContainer->addLayout(rightArea, 2);

    // Combine header and body into main container
    mainContainer->addLayout(headerContainer, 1);
    mainContainer->addLayout(bodyContainer, 9);

    // Set window properties
    setWindowTitle("Home");
    setMinimumWidth(400);
    setMinimumHeight(600);
}




Home::~Home()
{
    //todo:implement proper destructor
}

void Home::showUserInfo(){
        qDebug()<<"Id : "<<user->getId();
        qDebug()<<"Name : "<<user->getName();
        qDebug()<<"Email : "<<user->getEmail();
        qDebug()<<"DOB : "<<user->getDob();
        qDebug()<<"Bio : "<<user->getBio();
        qDebug()<<"Created At : "<<user->getCreatedAt();
}


void Home::loadThreads()
{
    // Retrieve all threads from the database
    threads = ThreadRepository::loadAllThreadsFromDb();
    qDebug() << "There are "<<threads.size()<< " threads loaded";

    // Clear existing widgets in centerArea
    QLayoutItem *item;
    while ((centerArea->takeAt(0)) != nullptr) {
        delete item->widget(); // Deletes the widget
        delete item;           // Deletes the layout item
    }

    // Create a ThreadWidget for each thread and add it to the centerArea layout
    for (const auto &thread : threads) {
        qDebug() <<"Creating widget for thread id : "<<thread.getThreadId();
        // Create the ThreadWidget using the parameterized constructor
        ThreadWidget *threadWidget = new ThreadWidget(
            QString::fromStdString(thread.getAuthorName()),
            QString::fromStdString(thread.getCreatedAt()),
            QString::fromStdString(thread.getTitle()),
            QString::fromStdString(thread.getContent()),
            thread.getThreadId(),
            this // Pass 'this' as the parent widget
            );

        // Add the ThreadWidget to the centerArea layout
        centerArea->addWidget(threadWidget);
    }

}

void Home::showThreads(){
    for(int i=0; i<threads.size(); i++){
        qDebug() << "Id : "<< threads[i].getThreadId() << "Title: "<< threads[i].getTitle();
    }
}

void Home::on_create_post_icon_clicked(){
    // Hide any currently visible widget and switch to post widget
    qDebug() << "Create Post Btn Clicked";
    // currentRightWidget->hide();
    // currentRightWidget = createPostWidget;
    // currentRightWidget->show();

}
void Home::on_search_triggered(){

}
void Home::on_message_icon_clicked(){
    qDebug() << "Message Btn Clicked";
}
void Home::on_profile_icon_clicked(){
    qDebug() << "Profiles Btn Clicked";
}

