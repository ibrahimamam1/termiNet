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

#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QBrush>
#include <QPen>

QImage AppHelper::createRoundedIcon(const QImage& inputImage) {
    // Resize the image to 50x50
    QImage resizedImage = inputImage.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Create a new transparent image of the same size
    QImage roundedImage(50, 50, QImage::Format_ARGB32);
    roundedImage.fill(Qt::transparent);

    // Create a painter to draw on the new image
    QPainter painter(&roundedImage);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Create a rounded rectangle path
    QPainterPath path;
    path.addRoundedRect(0, 0, 50, 50, 25, 25); // 25 is the radius for rounded corners (half of 50)

    // Set the clipping path to make the image rounded
    painter.setClipPath(path);

    // Draw the resized image onto the roundedImage
    painter.drawImage(0, 0, resizedImage);

    // Optionally, draw a border around the rounded image
    painter.setPen(QPen(Qt::black, 2)); // Border color and thickness
    painter.setBrush(Qt::NoBrush); // No fill
    painter.drawPath(path);

    return roundedImage;
}

QString AppHelper::hashString(const QString& target) {
    QByteArray byteArray = target.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);
    return hash.toHex();
}
