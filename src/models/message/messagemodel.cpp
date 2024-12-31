#include "messagemodel.h"

MessageModel::MessageModel() {}
MessageModel::MessageModel(UserModel& _otherUser, QString& text, QDateTime& time_s) : otherUser(_otherUser), content(text), timestamp(time_s){}
UserModel MessageModel::getOtherUser() const { return otherUser;}
QString MessageModel::getMessageContent() const { return content; }
QDateTime MessageModel::getTimestamp() const { return timestamp; }

