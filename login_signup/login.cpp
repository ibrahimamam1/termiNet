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
        return ;
    }

    // Retrieve and check the result
    if (q.next()) {
        login = q.value(0).toBool();
    } else {
        qDebug() << "No result returned from login_check function.";
    }

    if(login){

        UserModel *user = UserModel::getInstance();

        //get all user data and convert to user model
        q.prepare("SELECT * FROM users WHERE user_email=:email");
        q.bindValue(":email", QString::fromStdString(email));

        if(!q.exec()){
            qDebug() << "Failed to get Login Data\n";
            return ;
        }

        if(q.next()){
            user->setId(q.value(0).toInt());
            user->setName(q.value(1).toString().toStdString());
            user->setEmail(q.value(2).toString().toStdString());
            user->setSex(q.value(3).toString().toStdString());
            user->setDob(q.value(4).toString().toStdString());
            user->setBio(q.value(5).toString().toStdString());
            user->setCreatedAt(q.value(7).toString().toStdString());

            //debug test
            // qDebug()<<"Id : "<<user->getId();
            // qDebug()<<"Name : "<<user->getName();
            // qDebug()<<"Email : "<<user->getEmail();
            // qDebug()<<"DOB : "<<user->getDob();
            // qDebug()<<"Bio : "<<user->getBio();
            // qDebug()<<"Created At : "<<user->getCreatedAt();

            //Go to next screen here
            emit loginSuccessful();
        }

    }
    else{
        qDebug() << "Login Failed";
    }
}

