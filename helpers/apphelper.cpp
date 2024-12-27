#include "apphelper.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>
#include <QCryptographicHash>
#include <QDebug>

void AppHelper::saveUserForPersistentLogin(const int& user_id){

    //Get standart config location
    QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (configLocation.isEmpty()) {
        qWarning() << "Could not determine writable config location.";
        return;
    }

    // Create the application-specific directory if it doesn't exist
    QDir appConfigDir(configLocation + "/terminet");
    if (!appConfigDir.exists()) {
        if (!appConfigDir.mkpath(".")) { // "." creates the current directory
            qWarning() << "Failed to create application config directory.";
            return;
        }
    }

    QString path = appConfigDir.absoluteFilePath("login.txt");
    QFile file(path);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << path << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n";
    out << user_id << "\n";

    file.flush();
    file.close();

    qDebug() << "User ID saved for persistent login to:" << path; // For debugging
}

const int AppHelper::checkPersitentLogin(){

    QString configLocation = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    if (configLocation.isEmpty()) {
        qWarning() << "Could not determine writable config location.";
        return -1;
    }
    QString path = configLocation + "/terminet/login.txt";
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Failed to open file for reading:" << path << file.errorString(); // Changed "writing" to "reading"
        return -1;
    }

    QTextStream in(&file);

    // Skip the first line (date and time)... will probably do something with it later
    if (in.atEnd()) {
        qWarning() << "Login file is empty or missing timestamp.";
        file.close();
        return -1;
    }
    in.readLine();

    // Read the user ID
    if (in.atEnd()) {
        qWarning() << "Login file is incomplete, missing user ID.";
        file.close();
        return -1;
    }
    QString userIdStr = in.readLine();
    bool ok;
    int userId = userIdStr.toInt(&ok);

    if (!ok) {
        qWarning() << "Failed to convert user ID from string:" << userIdStr;
        file.close();
        return -1;
    }

    file.close();
    return userId;
}
