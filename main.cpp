#include "mainwindow.h"
#include "login_signup/signup.h"
#include "login_signup/login.h"
#include "db/databasemanager.h"
#include "screens/home/home.h"
#include "tests/login_signup/signup_test.h"
#include "models/usermodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager *db = new DatabaseManager();
    UserModel *user = UserModel::getInstance();
    Home* homePage = new Home();


    if(db->connect()){

        Login* loginWindow = new Login(nullptr);


        //user logged in, i want to destroy the login window and control to come back here
        QObject::connect(loginWindow, &Login::loginSuccessful, [&]() {
            loginWindow->deleteLater();           // Destroy login window
            homePage->setUser(user);
            homePage->show();            // Show home page
        });

        loginWindow->show();
    }
    else qDebug() << "Please Check Your DB Connection\n";

    //test_validate_signup_form();
    return a.exec();
}
