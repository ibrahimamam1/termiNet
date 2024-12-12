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
    communityPage = new CommunityPage();

    centerArea->addWidget(threadView);
    centerArea->addWidget(communityPage);

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
            qDebug() << "Inside Home: Switching to comment screen for thread ID:" << parentThreadID;
            savedThreads = threads;

            qDebug() << "Okay cleared center widget";

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

            //setup reply box
            QTextEdit *reply = new QTextEdit(this);
            reply->setPlaceholderText("Your Reply...");

            QHBoxLayout *replyButtonContainer = new QHBoxLayout();
            QPushButton *replyButton = new QPushButton("Post", this);

            connect(replyButton, &QPushButton::clicked, this, [this, reply, parentThreadID]() {
                qDebug() << "Yup you want to comment a thread huh";
                QString title = "";
                QString text = reply->toPlainText();

                UserModel *user = AuthenticatedUser::getInstance();
                ThreadModel thread(0, title, text,0, "", *user, -1, parentThreadID);
                ThreadRepository::addThreadtoDb(thread);

                reply->clear();
            });

            replyButtonContainer->addStretch(2);
            replyButtonContainer->addWidget(replyButton, 1);
            replyButtonContainer->addStretch(2);

            replyContainer->addWidget(reply, 3);
            replyContainer->addLayout(replyButtonContainer, 2);

            // // // Assemble the comment section layout
            commentSection->addWidget(goBack, 1);
            commentSection->addLayout(parentThreadContainer, 2);
            commentSection->addLayout(commentsContainer, 8);
            commentSection->addLayout(replyContainer, 2);



            //centerArea->addLayout(commentSection);
}






