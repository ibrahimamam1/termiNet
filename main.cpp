#include "mainwindow.h"
#include "login_signup/signup.h"
#include "login_signup/login.h"
#include "db/databasemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseManager *db = new DatabaseManager();
    //MainWindow w;
    //w.show();

    if(db->connect()){
        db->delete_schema();
        db->create_schema();
        Signup* signupWindow = new Signup(nullptr, db);
        signupWindow->show();
    }
    else qDebug() << "Please Check Your DB Connection\n";
    return a.exec();
}
