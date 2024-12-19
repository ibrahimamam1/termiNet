#include "apiclient.h"
#include <QJsonDocument>

ApiClient* ApiClient::instance = nullptr;

ApiClient::ApiClient(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);
}

QNetworkReply* ApiClient::makeGetRequest(const QString &url){
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = manager->get(request);
    return reply;

}
QNetworkReply* ApiClient::makePostRequest(const QString &url, const QJsonObject& data){
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QJsonDocument doc(data);
    QByteArray jsonData = doc.toJson();

    QNetworkReply *reply = manager->post(request, jsonData);
    return reply;

}

ApiClient* ApiClient::getInstance() {
    if(instance == nullptr)
        instance = new ApiClient();
    return instance;
}
const QString& ApiClient::getLoginUrl() const{ return loginUrl;}
const QString& ApiClient::getSignupUrl() const{ return signupUrl;}
