#include "mainwindow.h"
#include "login_signup/signup.h"
#include "login_signup/login.h"
#include "screens/home/home.h"
#include "models/user/usermodel.h"
#include "db/user/user_repository.h"

#include <QApplication>
#include <QMessageBox>
#include "helpers/apphelper.h"
#include "helpers/websocket_client/websocketclient.h"
#include "src/db/manager/databasemanager.h"

Home* Home::instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QEventLoop loop;
    bool initializationComplete = false;

    int userId = AppHelper::checkPersitentLogin();
    if(userId == -1){
        // Create and show login window
        auto loginWindow = new Login();
        loginWindow->setAttribute(Qt::WA_DeleteOnClose); // Auto-delete when closed
        QObject::connect(loginWindow, &Login::loginSuccessful, [&]() {
            initializationComplete = true;
            loginWindow->deleteLater();
            loop.quit();
        });
        loginWindow->show();
    }else{
        UserModel user = UserRepository::getUserFromId(userId);
        AuthenticatedUser::setInstance(user);
        initializationComplete = true;
        loop.quit();
    }

    if(!initializationComplete)
        loop.exec();

    //initialise database
    if(!DatabaseManager::init())
        qDebug() << "Failed to initialise database";

    //open websocket with server
    WebSocketClient& webSocket = WebSocketClient::getInstance();
    webSocket.connectToServer();


    //show homepage
    auto homePage = Home::getInstance();
    homePage->setAttribute(Qt::WA_DeleteOnClose);
    homePage->show();

    return a.exec();
}
