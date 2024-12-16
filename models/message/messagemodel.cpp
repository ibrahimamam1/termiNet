#include "messagemodel.h"

MessageModel::MessageModel() {}
MessageModel::MessageModel(const UserModel& sen, UserModel& rcv, QString& prev, QString& text) : sender(sen), receiver(rcv), preview(prev), content(text){}
UserModel MessageModel::getSender() const { return sender;}
UserModel MessageModel::getReceiver() const { return receiver;}
QString MessageModel::getMessagePreview() const { return preview;}
QString MessageModel::getMessageContent() const { return content; }
