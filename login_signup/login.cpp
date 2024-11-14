#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_btn_clicked()
{
    std::string email = ui->login_email->text().toStdString();
    std::string pass = ui->login_pass->text().toStdString();
    bool login = false;

    qDebug() << "email: "<< email << " pass: "<< pass;

    QSqlQuery q;
    q.prepare("SELECT login_check(:email, :password)");

    q.bindValue(":email", QString::fromStdString(email));
    q.bindValue(":password", QString::fromStdString(pass));

    // Execute the query
    if (!q.exec()) {
        qDebug() << "Error executing login_check:" << q.lastError().text();
    }

    // Retrieve and check the result
    if (q.next()) {
        login = q.value(0).toBool();
    } else {
        qDebug() << "No result returned from login_check function.";
    }

    if(login){
        qDebug() << "Login Successfull , to next page";
    }
    else{
        qDebug() << "Login Failed";
    }
}

