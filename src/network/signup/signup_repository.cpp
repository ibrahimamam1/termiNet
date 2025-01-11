#include "signup_repository.h"
#include "../../../helpers/api_client/apiclient.h"
#include "../../../helpers/apphelper.h"
#include "../../../helpers/hash_helper/hashhelper.h"
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
SignupRepository::SignupRepository() {}

int SignupRepository::createNewUserAccount(const int code, const QString& name, const QString& email, const QDate& dateOfBirth, const QString& password, QString& error_msg) {

    QJsonObject jsonData;
    jsonData["user_name"] = name;
    jsonData["user_email"] = email;
    jsonData["user_dob"] = dateOfBirth.toString("yyyy-MM-dd");
    jsonData["user_bio"] = "";
    jsonData["password"] = HashHelper::hashString(password);
    jsonData["created_at"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

    ApiClient& apiClient = ApiClient::getInstance();
    QString url = apiClient.getUserDataUrl() + QString::number(code) + "/";
    QNetworkReply* reply = apiClient.makePostRequest(url, jsonData, "");

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll()).object();
            if (responseJson.contains("Status") && responseJson["Status"].toString() == "Created") {
                error_msg = "OK";
                return 0;
            } else {
                error_msg = responseJson["Status"].toString();
                return 1;
            }
        } else {
            error_msg = reply->errorString();
            return 1
        }
        reply->deleteLater();
    });
    return 0;
}
const GoogleReply SignupRepository::googleSignup(){
    qDebug() << "Signup Repository: signup with google";
    auto google = new QOAuth2AuthorizationCodeFlow();
    google->setScope("email");

    QObject::connect(google, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);

    // Load Google OAuth2 credentials from JSON file
    const QJsonDocument document = AppHelper::loadJsonFromFile(":/src/network/login/google_auth.json");
    const auto object = document.object();

    const auto settingsObject = object["installed"].toObject();
    const QUrl authUri(settingsObject["auth_uri"].toString());
    const QString clientId = settingsObject["client_id"].toString();
    const QUrl tokenUri(settingsObject["token_uri"].toString());
    const QString clientSecret(settingsObject["client_secret"].toString());
    const auto redirectUris = settingsObject["redirect_uris"].toArray();
    const QUrl redirectUri(redirectUris[0].toString());
    const auto port = static_cast<quint16>(redirectUri.port());

    // Set OAuth2 parameters
    google->setAuthorizationUrl(authUri);
    google->setAccessTokenUrl(tokenUri);
    google->setClientIdentifier(clientId);
    google->setClientIdentifierSharedKey(clientSecret);

    // Set up the reply handler
    auto replyHandler = new QOAuthHttpServerReplyHandler(port);
    google->setReplyHandler(replyHandler);

    QEventLoop loop;
    GoogleReply googleReply;

    // Connect to the granted signal to capture the response
    QObject::connect(google, &QOAuth2AuthorizationCodeFlow::granted, [&]() {
        qDebug() << "OAuth2 flow completed successfully!";
        googleReply.accessToken = google->token();
        googleReply.refreshToken = google->refreshToken();
        googleReply.idToken = extra["id_token"].toString();
        googleReply.expirationDate = google->expirationAt();
        loop.quit();
    });

    // Handle errors
    QObject::connect(google, &QOAuth2AuthorizationCodeFlow::error, [&](const QString &error, const QString &errorDescription) {
        qDebug() << "OAuth2 error:" << error << "-" << errorDescription;
        loop.quit();
    });

    // Start the OAuth2 flow
    google->grant();

    loop.exec();

    // Clean up
    google->deleteLater();
    replyHandler->deleteLater();

    qDebug() << "Signup Repository: signup with google will return";
    return googleReply;
}
int SignupRepository::createNewUserAccountWithEmailAndPassword(const QString& name, const QString& email,
                                                               const QDate& dateOfBirth, const QString& password, QString& error_msg){
    return createNewUserAccount(1, name, email, dateOfBirth, password, error_msg);
}
int SignupRepository::createNewUserAccountWithGoogle(const QString& name, const QDate& dateOfBirth, QString& error_msg){
    return createNewUserAccount(2, name, "", dateOfBirth, "", error_msg);
}
