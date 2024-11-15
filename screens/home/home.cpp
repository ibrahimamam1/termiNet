#include "home.h"
#include "ui_home.h"

Home::Home(QWidget *parent) : QMainWindow(parent), ui(new Ui::Home), user(nullptr)
{
    ui->setupUi(this);
    createPostWidget = new CreatePost(this);
    createPostWidget->hide();

    currentRightWidget = createPostWidget;
    ui->rightArea->addWidget(currentRightWidget);

}

void Home::setUser(UserModel *usr){
    user = usr;
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

void Home::on_create_post_btn_clicked()
{
    // Hide any currently visible widget and switch to post widget

    currentRightWidget->hide();
    currentRightWidget = createPostWidget;
    currentRightWidget->show();
    showUserInfo();

}

