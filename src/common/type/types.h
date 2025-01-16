#ifndef TYPES_H
#define TYPES_H
#include <QString>
#include <QDateTime>

enum LoginResult {SUCCESS, FAILED, SERVER_ERROR, NETWORK_ERROR};

//google reply
typedef struct{
    QString accessToken;
    QString refreshToken;
    QString googleUserId;
    QString email;
    QDateTime expirationDate;
}GoogleReply ;

#endif // TYPES_H
