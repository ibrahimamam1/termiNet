#include "storagerepository.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QHttpMultiPart>
#include <QtNetwork/QHttpPart>
#include <QFile>

StorageRepository::StorageRepository() {}
void StorageRepository::uploadToStorage(QString& filepath, QString& bucketName){
    QNetworkAccessManager *networkManager = new QNetworkAccessManager();

    QFile *file = new QFile(filepath);
    if(!file->open(QIODevice::ReadOnly)){
        qWarning() << "Failed to open file: " << filepath;
        return;
    }

    QHttpMultiPart *payload = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart *data;
    data->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + file->fileName() + "\""));
    data->setBodyDevice(file);
    file->setParent(payload);
    payload->append(data);

    //create the request
    QUrl url(QString("%1/storage/v1/objects/%2/uploads/%3").arg(AppConstant::supaBaseUrl, bucketName, file->fileName()));
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", QString("Bearer %1").arg(AppConstant::supaBaseKey).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");

    //send the request
    QNetworkReply reply = networkManager->post(request, payload);
    payload->setParent(reply);

    //handle response
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "File uploaded successfully!";
            qDebug() << "Response:" << reply->readAll();
        } else {
            qWarning() << "Error uploading file:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
