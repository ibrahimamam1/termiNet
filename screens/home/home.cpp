#include "home.h"
#include<QTextBrowser>

Home::Home(QWidget *parent) : QMainWindow(parent), user(AuthenticatedUser::getInstance())
{
    threads = ThreadRepository::loadAllThreadsFromCommunity(-1);

    // Create a central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout
    mainContainer = new QVBoxLayout(centralWidget);

    topBar = new CustomTopBar();
    leftNav = new LeftNavigationWidget();

    // Center area layout
    centerArea = new QStackedWidget();
    threadView = new ThreadView(threads);

    centerArea->addWidget(threadView);

    // Body layout
    bodyContainer = new QHBoxLayout();
    bodyContainer->addWidget(leftNav, 2);
    bodyContainer->addWidget(centerArea, 8);

    // Combine header and body into main container
    mainContainer->addWidget(topBar, 1);
    mainContainer->addLayout(bodyContainer, 9);

    // Set window properties
    setWindowTitle("Home");
    setMinimumWidth(400);
    setMinimumHeight(600);

}


Home* Home::getInstance(){

    if(instance == nullptr){
        instance = new  Home();
    }
    return instance;
}

Home::~Home()
{
    //todo:implement proper destructor
}



void Home::onCommentBtnClicked(int parentThreadID){

            // Create layouts for comment screen
            QVBoxLayout *commentSection = new QVBoxLayout();

            QPushButton *goBack = new QPushButton();
            goBack->setText("Back");

            QVBoxLayout *parentThreadContainer = new QVBoxLayout();
            QVBoxLayout *commentsContainer = new QVBoxLayout();
            QVBoxLayout *replyContainer = new QVBoxLayout();

            //get parent thread using ThreadID
            ThreadModel parentThread = ThreadRepository::getSingleThread(parentThreadID);
            ThreadWidget *parentThreadWidget = new ThreadWidget(parentThread, this);

            parentThreadContainer->addWidget(parentThreadWidget);

            //Fetch and display comments
            threads.clear();
            threads = ThreadRepository::loadAllCommentsFromDb(parentThreadWidget->getThreadId());
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






