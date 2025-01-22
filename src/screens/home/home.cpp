#include "home.h"
#include "../../network/websocket/websocketclient.h"
#include "../../db/manager/databasemanager.h"
#include "../../network/search/search_repository.h"
#include<QTextBrowser>
#include<QTimer>
#include <QMessageBox>

Home::Home(QWidget *parent) : QMainWindow(parent), user(AuthenticatedUser::getInstance())
{
    threads = ThreadRepository::loadAllThreads();

    // Create a central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout
    mainContainer = new QVBoxLayout(centralWidget);

    topBar = new CustomTopBar();
    connect(topBar, &CustomTopBar::postCreated, this, &Home::onPostCreated);
    connect(topBar, &CustomTopBar::messageIconClicked, this, &Home::onMessageIconClicked);
    connect(topBar, &CustomTopBar::profileIconClicked, this, &Home::onProfileIconClicked);
    connect(topBar, &CustomTopBar::searchActivated, this, &Home::onSearchActivated);
    leftNav = new LeftNavigationWidget();
    connect(leftNav, &LeftNavigationWidget::homeClicked, this, [this]{
        if(centerArea->currentIndex() == 0){
            threadView->switchToHomeScreen();
        }else{
            centerArea->setCurrentIndex(0);
        }

    });

    // Center area layout
    centerArea = new QStackedWidget();
    threadView = new ThreadView(threads);
    communityPage = new CommunityPage();
    searchView = new SearchView();

    centerArea->addWidget(threadView);
    centerArea->addWidget(communityPage);
    centerArea->addWidget(searchView);

    //setup profile view
    profileview = new ProfileView(this);
    profileview->hide();
    profileVisible = false;

    // Body layout
    bodyContainer = new QHBoxLayout();
    bodyContainer->addWidget(leftNav, 2);
    bodyContainer->addWidget(centerArea, 6);
    bodyContainer->addWidget(profileview, 1);

    // Combine header and body into main container
    mainContainer->addWidget(topBar, 1);
    mainContainer->addLayout(bodyContainer, 9);


    //setup message page
    msgPage = new MessagePage();
    connect(&WebSocketClient::getInstance(), &WebSocketClient::messageReceived,msgPage, &MessagePage::onMessageReceived);




    // Set window properties
    setWindowTitle("Home");
    setMinimumWidth(400);
    setMinimumHeight(600);

}


Home& Home::getInstance(){

    if(instance == nullptr){
        instance = std::make_unique<Home>();
    }
    return *instance;
}

Home::~Home()
{
    //todo:implement proper destructor
}



void Home::onCommentBtnClicked(const ThreadModel& parentThread){

    // Create layouts for comment screen
    QVBoxLayout *commentSection = new QVBoxLayout();

    QPushButton *goBack = new QPushButton();
    goBack->setText("Back");

    QVBoxLayout *parentThreadContainer = new QVBoxLayout();
    QVBoxLayout *commentsContainer = new QVBoxLayout();
    QVBoxLayout *replyContainer = new QVBoxLayout();

    ThreadWidget *parentThreadWidget = new ThreadWidget(parentThread, this);

    parentThreadContainer->addWidget(parentThreadWidget);

    //Fetch and display comments
    threads.clear();
    threads = ThreadRepository::loadAllThreadsFromParentThread(parentThreadWidget->getThreadId());
    for (const auto &thread : threads) {
        ThreadWidget *commentWidget = new ThreadWidget(thread, this);
        commentsContainer->addWidget(commentWidget);
    }
    commentsContainer->addStretch(1);



    // // // Assemble the comment section layout
    commentSection->addWidget(goBack, 1);
    commentSection->addLayout(parentThreadContainer, 2);
    commentSection->addLayout(commentsContainer, 8);
    commentSection->addLayout(replyContainer, 2);



    //centerArea->addLayout(commentSection);
}


void Home::onMessageIconClicked(){
    DatabaseManager& db = DatabaseManager::getInstance();
    std::vector convos = db.getAllConversations();
    msgPage->messageListView->setConverstaion(convos);
    msgPage->show();
}

void Home::onProfileIconClicked(){
    if(profileVisible){
        profileVisible = false;
        profileview->hide();
    }
    else{
        profileVisible = true;
        profileview->show();
    }
}

void Home::onPostCreated(bool success){
    //show toast message
    QLabel *messageLabel = new QLabel();
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setStyleSheet(success ? "color: green;" : "color: red;");
    messageLabel->setText(success ? "Post created successfully!" : "Failed to create post.");

    mainContainer->addWidget(messageLabel);

    // Timer to remove the message after 3 seconds
    QTimer::singleShot(5000, [this, messageLabel]() {
        mainContainer->removeWidget(messageLabel);
        delete messageLabel;
    });
}

void Home::onSearchActivated(const QString& searchString){
    qDebug() << "Initiating search For: " << searchString;
    QList<ThreadModel>threads;
    QList<CommunityModel>communities;
    QList<UserModel>users;

    int err = SearchRepository::searchFor(searchString, threads, communities, users);
    if(err){
        QMessageBox::critical(this, "Error", "Connection Error. Please try again", "OK");
        return;
    }
    qDebug() << "Search result are here hoorah";
    qDebug() << "Found threads : " << threads.size();
    qDebug() << "Found comms : " << communities.size();
    qDebug() << "Found users : " << users.size();
    searchView->setSearchView(threads, communities, users);
    centerArea->setCurrentIndex(2);
}



