#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include "../../../src/models/user/usermodel.h"
#include <QDateTime>

class MessageModel
{
    UserModel receiver;
    QString content;
    QDateTime timestamp;
public:
    MessageModel();
    MessageModel(UserModel& rcv, QString& text, QDateTime& time_s);
    UserModel getReceiver() const;
    QString getMessageContent() const;
    QDateTime getTimestamp() const;

};

#endif // MESSAGEMODEL_H
