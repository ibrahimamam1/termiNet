#include "apphelper.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>
#include <QCryptographicHash>
#include <QDebug>
#include <QApplication>

void AppHelper::saveUserForPersistentLogin(const QString& user_id){

    //Get standart config location
    QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (configLocation.isEmpty()) {
        qWarning() << "Could not determine writable config location.";
        return;
    }

    // Create the application-specific directory if it doesn't exist
    QDir appConfigDir(configLocation);
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

const QString AppHelper::checkPersitentLogin(){

    QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (configLocation.isEmpty()) {
        qWarning() << "Could not determine writable config location.";
        return "";
    }
    QString path = configLocation + "/login.txt";
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Failed to open file for reading:" << path << file.errorString(); // Changed "writing" to "reading"
        return "";
    }

    QTextStream in(&file);

    // Skip the first line (date and time)... will probably do something with it later
    if (in.atEnd()) {
        qWarning() << "Login file is empty or missing timestamp.";
        file.close();
        return "";
    }
    in.readLine();

    // Read the user ID
    if (in.atEnd()) {
        qWarning() << "Login file is incomplete, missing user ID.";
        file.close();
        return "";
    }
    QString userIdStr = in.readLine();

    file.close();
    return userIdStr;
}

const QString AppHelper::getDefaultProfilePicturePath() {

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString profilePicPath = appDataPath + "/default_profile.png";

    QFileInfo fileInfo(profilePicPath);
    if (!fileInfo.exists()) {
        // Create directory if it doesn't exist
        QDir dir(appDataPath);
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        // Copy default profile picture from resources
        QString path = QApplication::applicationDirPath() + "/assets/default_profile.png";
        qDebug() << "File does not exist, will copy file from " << path;
        QFile::copy(path, profilePicPath);

        // Make sure the copied file is writable
        QFile file(profilePicPath);
        file.setPermissions(file.permissions() | QFileDevice::WriteOwner);
    }

    return profilePicPath;
}

const QJsonDocument AppHelper::loadJsonFromFile(const QString& filePath){

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open the JSON file.";
        return QJsonDocument();
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (document.isNull()) {
        qWarning() << "Failed to create JSON document.";
        return QJsonDocument();
    }

    return document;
}
