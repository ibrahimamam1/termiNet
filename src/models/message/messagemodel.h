#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include "../../../src/models/user/usermodel.h"
#include <QDateTime>

class MessageModel
{
    UserModel otherUser;
    QString content;
    QDateTime timestamp;
public:
    MessageModel();
    MessageModel(UserModel& _otherUser, QString& text, QDateTime& time_s);
    UserModel getOtherUser() const;
    QString getMessageContent() const;
    QDateTime getTimestamp() const;

};

#endif // MESSAGEMODEL_H
