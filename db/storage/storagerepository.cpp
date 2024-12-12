#include "storagerepository.h"
#include <QSqlQuery>
#include <QBuffer>
#include <QSqlError>

StorageRepository::StorageRepository() {}

QImage StorageRepository::getIconImage(QString& ref) {
    QSqlQuery q;
    q.prepare("SELECT filedata FROM iconsBucket WHERE filename = :reference");
    q.bindValue(":reference", ref);

    if (!q.exec()) {
        qDebug() << "Failed to retrieve icon image data: " << q.lastError();
        return QImage();
    }

    if (!q.next()) {
        qDebug() << "No image found for filename: " << ref;
        return QImage();
    }

    QByteArray data = q.value(0).toByteArray();
    QImage image;

    if (!image.loadFromData(data, "PNG")) {
        qDebug() << "Failed to load image from byte array";
        return QImage();
    }

    return image;
}

QImage StorageRepository::getBannerImage(QString& ref){
    QSqlQuery q;
    q.prepare("SELECT filedata FROM bannersBucket WHERE filename = :reference");
    q.bindValue(":reference", ref);

    if (!q.exec()) {
        qDebug() << "Failed to retrieve banner image data: " << q.lastError();
        return QImage();
    }

    if (!q.next()) {
        qDebug() << "No image found for filename: " << ref;
        return QImage();
    }

    QByteArray data = q.value(0).toByteArray();
    QImage image;

    if (!image.loadFromData(data, "PNG")) {
        qDebug() << "Failed to load image from byte array";
        return QImage();
    }

    return image;
}
