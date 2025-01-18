#include "src/screens/signup/signup.h"
#include "src/screens/login/login.h"
#include "screens/home/home.h"
#include "src/models/user/usermodel.h"
#include "src/network/user/user_repository.h"
#include "src/common/theme/apptheme.h"

#include <QApplication>
#include <QMessageBox>
#include <QStyleHints>
#include "helpers/apphelper.h"
#include "helpers/websocket_client/websocketclient.h"
#include "src/db/manager/databasemanager.h"

Home* Home::instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");

    QPalette darkPalette = AppTheme::getDarkPalette();
    QPalette lightPalette = AppTheme::getLightPalette();

    //check system theme
    bool isDarkMode = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;

    if(isDarkMode)
        a.setPalette(darkPalette);
    else
        a.setPalette(lightPalette);

    QEventLoop loop;
    bool initializationComplete = false;

    QString userId = AppHelper::checkPersitentLogin();
    if(userId.length() <= 5){
        // Create and show login/signup window
        auto loginWindow = new Login();
        auto signUpPage = new Signup();

        loginWindow->setAttribute(Qt::WA_DeleteOnClose);
        signUpPage->setAttribute(Qt::WA_DeleteOnClose);

        auto stackedWidget = new QStackedWidget;
        stackedWidget->addWidget(loginWindow);
        stackedWidget->addWidget(signUpPage);

        QObject::connect(loginWindow, &Login::loginSuccessful, [&]() {
            initializationComplete = true;
            stackedWidget->hide();
            loop.quit();
        });
        QObject::connect(signUpPage, &Signup::signupSuccessful, [&]() {
            initializationComplete = true;
            stackedWidget->hide();
            loop.quit();
        });
        QObject::connect(loginWindow, &Login::createAccountClicked, [&] () {
            stackedWidget->setCurrentIndex(1);
        });
        stackedWidget->show();
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
