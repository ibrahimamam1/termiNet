#include "messagemodel.h"

MessageModel::MessageModel() {}
MessageModel::MessageModel(UserModel& rcv, QString& text, QDateTime& time_s) : receiver(rcv), content(text), timestamp(time_s){}
UserModel MessageModel::getReceiver() const { return receiver;}
QString MessageModel::getMessageContent() const { return content; }
QDateTime MessageModel::getTimestamp() const { return timestamp; }
