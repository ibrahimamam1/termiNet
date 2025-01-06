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

void LoginRepository::googleLogin(){
    auto google = new QOAuth2AuthorizationCodeFlow();
    google->setScope("email");

    QObject::connect(google, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    const QJsonDocument document = AppHelper::loadJsonFromFile(":/src/network/login/google.json");
    const auto object = document.object();
    const auto settingsObject = object["installed"].toObject();
    const QUrl authUri(settingsObject["auth_uri"].toString());
    const QString clientId = settingsObject["client_id"].toString();
    const QUrl tokenUri(settingsObject["token_uri"].toString());
    const QString clientSecret(settingsObject["client_secret"].toString());
    const auto redirectUris = settingsObject["redirect_uris"].toArray();
    const QUrl redirectUri(redirectUris[0].toString());
    const auto port = static_cast<quint16>(redirectUri.port());

    google->setAccessTokenUrl(authUri);
    google->setClientIdentifier(clientId);
    google->setAccessTokenUrl(tokenUri);
    google->setClientIdentifierSharedKey(clientSecret);

    auto replyHandler = new QOAuthHttpServerReplyHandler(port);
    google->setReplyHandler(replyHandler);

    google->grant();


}

