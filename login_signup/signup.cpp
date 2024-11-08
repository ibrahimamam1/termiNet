#include "signup.h"
#include "ui_signup.h"
#include<iostream>
#include<string>

Signup::Signup(QWidget *parent, DatabaseManager* instance)
    : QDialog(parent)
    , ui(new Ui::Signup)
    , db(instance)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_create_account_btn_clicked()
{
    qDebug() << "Retreiving Data From Form";

    std::string


}

