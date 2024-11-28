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
    logo = new QLabel(this);
    logo->setPixmap(QPixmap("../../assets/logo.png"));
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search...");
    connect(searchBar, &QLineEdit::returnPressed, this, &Home::on_search_triggered);

    createPostIcon = new ClickableLabel(this);
    createPostIcon->setPixmap(QPixmap("../../assets/createPost.png"));
    createPostIcon->setCursor(Qt::PointingHandCursor);
    connect(createPostIcon, &ClickableLabel::clicked, this, &Home::onCreatePostIconClicked);

    messageIcon = new ClickableLabel(this);
    messageIcon->setPixmap(QPixmap("../../assets/messageIcon.png"));
    messageIcon->setCursor(Qt::PointingHandCursor);
    messageIcon->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(messageIcon, &QLabel::linkActivated, this, &Home::on_message_icon_clicked);

    profileIcon = new ClickableLabel(this);
    profileIcon->setPixmap(QPixmap("../../assets/profileIcon.png"));
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
    communityLabel = new QLabel("Communities", this);
    createCommunity = new QLabel(this);
    createCommunity->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Create Community?</a>");
    createCommunity->setTextFormat(Qt::RichText);
    createCommunity->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(createCommunity, &QLabel::linkActivated, this, &Home::onCreateCommunityBtnClicked);

    communityNav->addWidget(communityLabel);
    communityNav->addWidget(createCommunity);
    communityNav->addStretch();

    QScrollArea* communityScrollArea = new QScrollArea(this);
    QWidget* communityContent = new QWidget(this);
    communityContent->setLayout(communityNav);
    communityScrollArea->setWidget(communityContent);
    communityScrollArea->setWidgetResizable(true);

    leftArea->addLayout(homeNav, 2);
    leftArea->addWidget(communityScrollArea, 8);

    // Center area layout
    threadsArea = new QVBoxLayout(); // Threads will be dynamically added here.
    centerArea = threadsArea;

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
    qDebug() << "There are " << threads.size() << " threads loaded";

    clearCenterWidget();
    addThreadsToCenterWidget();

}


void Home::showThreads(){
    for(int i=0; i<threads.size(); i++){
        qDebug() << "Id : "<< threads[i].getThreadId() << "Title: "<< threads[i].getTitle();
    }
}

void Home::onCreatePostIconClicked(){
    // Hide any currently visible widget and switch to post widget
    qDebug() << "Create Post Btn Clicked";
    currentRightWidget->hide();
    currentRightWidget = createPostWidget;
    currentRightWidget->show();

}
void Home::on_search_triggered(){

}
void Home::on_message_icon_clicked(){
    qDebug() << "Message Btn Clicked";
}
void Home::on_profile_icon_clicked(){
    qDebug() << "Profiles Btn Clicked";
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
            connect(goBack, &QPushButton::clicked , this, &Home::goBackToHomePressed);

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



            centerArea->addLayout(commentSection);
}

void Home::goBackToHomePressed(){

    clearCenterWidget();
    qDebug() << "Should Clear Center Widget";
    threads.clear();
    threads = savedThreads;
    addThreadsToCenterWidget();
    centerArea->addLayout(threadsArea);

}

void Home::clearCenterWidget(){
    QLayoutItem *item;
    while ((item = centerArea->takeAt(0)) != nullptr) {
        delete item->widget(); // Deletes the widget
        delete item;           // Deletes the layout item
    }

}

void Home::addThreadsToCenterWidget(){
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
        threadsArea->addWidget(threadWidget);

        connect(threadWidget, &ThreadWidget::switchToCommentScreen, this, &Home::onCommentBtnClicked);

    }
}

void Home::onCreateCommunityBtnClicked(){
    qDebug() << "Create Community Button clicked";
}




