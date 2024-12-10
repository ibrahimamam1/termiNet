#include "home.h"
#include<QTextBrowser>

Home::Home(QWidget *parent) : QMainWindow(parent), user(UserModel::getInstance())
{
    // Create a central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout
    mainContainer = new QVBoxLayout(centralWidget);

    topBar = new CustomTopBar();
    leftNav = new LeftNavigationWidget();

    // Center area layout
    centerArea = new QStackedWidget();
    homeThreads = new QWidget();
    homeThreadsLayout = new QVBoxLayout(homeThreads);
    communityPage = new CommunityPage();

    centerArea->addWidget(homeThreads);
    centerArea->addWidget(communityPage);



    // Right area layout
    rightArea = new QVBoxLayout();
    currentRightWidget = new QLabel("Right Widget Placeholder", this); // Replace dynamically as needed.
    rightArea->addWidget(currentRightWidget);

    // Body layout
    bodyContainer = new QHBoxLayout();
    bodyContainer->addWidget(leftNav, 2);
    bodyContainer->addWidget(centerArea, 6);
    bodyContainer->addLayout(rightArea, 2);

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

void Home::loadThreads()
{
    // Retrieve all threads from the database
    threads = ThreadRepository::loadAllThreadsFromDb();

    //clearCenterWidget();

    for (const auto &thread : threads) {
        qDebug() << "Creating widget for thread ID:" << thread.getThreadId();

        // Create the ThreadWidget
        ThreadWidget *threadWidget = new ThreadWidget(
            QString::fromStdString(thread.getAuthorName()),
            QString::fromStdString(thread.getCreatedAt()),
            QString::fromStdString(thread.getTitle()),
            QString::fromStdString(thread.getContent()),
            thread.getCommentCount(),
            thread.getThreadId(),
            this // Pass 'this' as the parent widget
            );

        // Add the ThreadWidget to the threadsArea layout
        homeThreadsLayout->addWidget(threadWidget);

        connect(threadWidget, &ThreadWidget::switchToCommentScreen, this, &Home::onCommentBtnClicked);

    }

}


void Home::onCommentBtnClicked(int parentThreadID){
            qDebug() << "Inside Home: Switching to comment screen for thread ID:" << parentThreadID;
            savedThreads = threads;

            clearCenterWidget();
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
            ThreadWidget *parentThreadWidget = new ThreadWidget(
                                                   QString::fromStdString(parentThread.getAuthorName()),
                                                   QString::fromStdString(parentThread.getCreatedAt()),
                                                   QString::fromStdString(parentThread.getTitle()),
                                                   QString::fromStdString(parentThread.getContent()),
                                                   parentThread.getCommentCount(),
                                                   parentThread.getThreadId(),
                                                   this
                );

            parentThreadContainer->addWidget(parentThreadWidget);

            //Fetch and display comments
            threads.clear();
            threads = ThreadRepository::loadAllCommentsFromDb(parentThreadWidget->getThreadId());
            for (const auto &thread : threads) {
                ThreadWidget *commentWidget = new ThreadWidget(
                    QString::fromStdString(thread.getAuthorName()),
                    QString::fromStdString(thread.getCreatedAt()),
                    QString::fromStdString(thread.getTitle()),
                    QString::fromStdString(thread.getContent()),
                    thread.getCommentCount(),
                    thread.getThreadId(),
                    this
                    );
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

                UserModel *user = UserModel::getInstance();
                ThreadModel thread(0, title.toStdString(), text.toStdString(),0, "", user->getId(), -1, parentThreadID);
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


void Home::clearCenterWidget(){
    QLayoutItem *item;
    while ((item = homeThreadsLayout->takeAt(0)) != nullptr) {
        delete item->widget(); // Deletes the widget
        delete item;           // Deletes the layout item
    }

}





