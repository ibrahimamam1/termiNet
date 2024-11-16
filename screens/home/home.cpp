#include "home.h"
#include "ui_home.h"
#include<QTextBrowser>

Home::Home(QWidget *parent) : QMainWindow(parent), ui(new Ui::Home), user(UserModel::getInstance())
{
    ui->setupUi(this);
    createPostWidget = new CreatePost(this);
    createPostWidget->hide();

    currentRightWidget = createPostWidget;
    ui->rightArea->addWidget(currentRightWidget);
}


Home::~Home()
{
    delete ui;
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
    while ((item = ui->centerArea->takeAt(0)) != nullptr) {
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
        ui->centerArea->addWidget(threadWidget);
    }

}

void Home::showThreads(){
    for(int i=0; i<threads.size(); i++){
        qDebug() << "Id : "<< threads[i].getThreadId() << "Title: "<< threads[i].getTitle();
    }
}

void Home::on_create_post_btn_clicked()
{
    // Hide any currently visible widget and switch to post widget

    currentRightWidget->hide();
    currentRightWidget = createPostWidget;
    currentRightWidget->show();
    showUserInfo();

}

