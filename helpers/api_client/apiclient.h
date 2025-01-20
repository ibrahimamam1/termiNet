#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = nullptr);
    QNetworkReply* makeGetRequest(const QString& url);
    QNetworkReply* makePostRequest(const QString& url, const QJsonObject& data);

    const QString& getLoginUrl() const;
    const QString& getSignupUrl() const;
    const QString& getUserDataUrl() const;
    const QString& getUpdateUserDataUrl() const;
    const QString& getPostThreadUrl() const;
    const QString& getThreadsUrl() const;
    const QString& getCategoriesUrl() const;
    const QString& getCommunitiesUrl() const;
    static ApiClient& getInstance();

private:

    static std::unique_ptr<ApiClient> instance;
    std::unique_ptr<QNetworkAccessManager> manager;
    const QString baseUrl = "http://127.0.0.1:8080/";
    const QString loginUrl = baseUrl + "login/";
    const QString signupUrl = baseUrl + "signup/";
    const QString userDataUrl = baseUrl + "users/";
    const QString updateUserDataUrl = baseUrl + "update/users/";
    const QString postThreadUrl = baseUrl + "threads/new/";
    const QString threadsUrl = baseUrl + "threads/";
    const QString categoryUrl = baseUrl + "categories/";
    const QString communityUrl = baseUrl + "communities/";

signals:
private slots:
    void handleNetworkError(QNetworkReply::NetworkError);
};

#endif // APICLIENT_H
