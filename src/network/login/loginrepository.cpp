#include "loginrepository.h"
#include "../../../helpers/api_client/apiclient.h"
#include "../../../helpers/apphelper.h"
#include <QPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QEventLoop>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>

LoginRepository::LoginRepository() {}

LoginResult LoginRepository::login(const QString& email, const QString& pass){

    //prepare login URI
    ApiClient& apiclient = ApiClient::getInstance();
    QString loginUri = apiclient.getLoginUrl() + email + "/" + pass;

    //Make login Request to server
    QPointer<QNetworkReply> safeLoginReply(apiclient.makeGetRequest(loginUri));

    //Wait for response
    QEventLoop loop;
    LoginResult loginResult;

    QObject::connect(safeLoginReply, &QNetworkReply::finished, [&]() {

        if (safeLoginReply && safeLoginReply->error() == QNetworkReply::NoError) {
            QByteArray data = safeLoginReply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();
                if (jsonObject.contains("body")) {
                    QJsonObject body = jsonObject["body"].toObject();
                    bool success = body["Grant Access"].toBool();
                    loginResult = success ? LoginResult::SUCCESS : LoginResult::FAILED;
                }
            } else {
                qDebug() << "Invalid response format, not a json object";
                loginResult = LoginResult::SERVER_ERROR;
            }
        } else {
            qDebug() << "Login Error:" << safeLoginReply->errorString();
            loginResult = LoginResult::NETWORK_ERROR;
        }
        safeLoginReply->deleteLater();
        loop.quit();
    });

    // Wait for the request to complete
    loop.exec();
    return loginResult;
}

LoginResult LoginRepository::googleLogin(QString& googleId) {
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
    LoginResult result = LoginResult::FAILED;

    // Connect to the granted signal to capture the response
    QObject::connect(google, &QOAuth2AuthorizationCodeFlow::granted, [&]() {
        qDebug() << "OAuth2 flow completed successfully!";
        qDebug() << "Access Token:" << google->token();
        qDebug() << "Refresh Token:" << google->refreshToken();
        qDebug() << "Expiration Date:" << google->expirationAt();

        // Check if the access token is valid
        if (!google->token().isEmpty()) {
            auto extraTokens = google->extraTokens();
            googleId = extraTokens["id_token"].toString();
            result = LoginResult::SUCCESS;
        } else {
            result = LoginResult::FAILED;
        }

        loop.quit();
    });

    // Handle errors
    QObject::connect(google, &QOAuth2AuthorizationCodeFlow::error, [&](const QString &error, const QString &errorDescription) {
        qDebug() << "OAuth2 error:" << error << "-" << errorDescription;
        result = LoginResult::NETWORK_ERROR; // Login failed
        loop.quit();
    });

    // Start the OAuth2 flow
    google->grant();

    loop.exec();

    // Clean up
    google->deleteLater();
    replyHandler->deleteLater();

    return result;
}

