#include "apiclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "../../src/models/user/authenticateduser.h"

std::unique_ptr<ApiClient> ApiClient::instance = nullptr;

ApiClient::ApiClient(QObject *parent)
    : QObject{parent}
{
    manager = std::make_unique<QNetworkAccessManager>(this);
}

QNetworkReply* ApiClient::makeGetRequest(const QString &url){
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = manager->get(request);
    return reply;

}
QNetworkReply* ApiClient::makePostRequest(const QString &url, const QJsonObject& data) {

    QNetworkRequest request(url);
    qDebug() << "Converting JSON...";
    QJsonDocument doc(data);
    QByteArray jsonData = doc.toJson();



    qDebug() << "Setting Headers...";
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(jsonData.size()));
    request.setRawHeader("X-Custom-Client-Header", "Qt-Client");

    qDebug() << "Making Request...";
    QNetworkReply *reply = manager->post(request, jsonData);
    qDebug() << "made request";
    // Connect signals for proper memory management
    connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
    connect(reply, &QNetworkReply::errorOccurred, this, &ApiClient::handleNetworkError);

    qDebug() << "Sent JSON:" << QString(jsonData);
    return reply;
}

void ApiClient::handleNetworkError(QNetworkReply::NetworkError error) {
    qWarning() << "Network error occurred:" << error;
}

ApiClient& ApiClient::getInstance() {
    if(instance == nullptr)
        instance = std::make_unique<ApiClient>();
    return *instance;
}
const QString& ApiClient::getLoginUrl() const{ return loginUrl;}
const QString& ApiClient::getSignupUrl() const{ return signupUrl;}
const QString& ApiClient::getUserDataUrl() const{ return userDataUrl;}
const QString& ApiClient::getUpdateUserDataUrl() const { return updateUserDataUrl; }
const QString& ApiClient::getPostThreadUrl() const {return postThreadUrl;}
