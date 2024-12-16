#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include "../user/usermodel.h"

class MessageModel
{
    UserModel sender;
    UserModel receiver;
    QString preview;
    QString content;
public:
    MessageModel();
    MessageModel(const UserModel& sen, UserModel& rcv, QString& prev, QString& text);
    UserModel getSender() const;
    UserModel getReceiver() const;
    QString getMessagePreview() const;
    QString getMessageContent() const;
};

#endif // MESSAGEMODEL_H
