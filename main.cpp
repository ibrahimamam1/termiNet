#include "mainwindow.h"
#include "login_signup/signup.h"
#include "login_signup/login.h"
#include "db/databasemanager.h"
#include "screens/home/home.h"
#include "models/user/usermodel.h"

#include <QApplication>
#include <QMessageBox>

Home* Home::instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create database manager
    DatabaseManager* db = DatabaseManager::getInstance();

    // Create and show login window
    auto loginWindow = new Login();
    loginWindow->setAttribute(Qt::WA_DeleteOnClose); // Auto-delete when closed
    loginWindow->show();

    //try to connect to database
    int retry = 0;
    while (!db->connect()) {
        //show error message
        QMessageBox retryBox;
        retryBox.setIcon(QMessageBox::Warning);
        retryBox.setWindowTitle("Connection Error");
        retryBox.setText("Failed to connect to Server");
        retryBox.setInformativeText(QString("Retrying..."));
        retryBox.exec();

        if(retry == 3){
            // all retries failed
            QMessageBox errorBox;
            errorBox.setIcon(QMessageBox::Critical);
            errorBox.setWindowTitle("Connection Error");
            errorBox.setText("Failed to connect to Server");
            errorBox.setInformativeText("Please check your internet connection and try again later.");
            errorBox.exec();
            return 1;
        }
        retry++;
    }


    // Connect login success signal
    QObject::connect(loginWindow, &Login::loginSuccessful, [loginWindow]() {
        auto homePage = Home::getInstance();
        homePage->setAttribute(Qt::WA_DeleteOnClose);
        homePage->show();
        loginWindow->deleteLater();
    });

    return a.exec();


}
