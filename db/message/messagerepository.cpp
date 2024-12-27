#include "messagerepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../user/user_repository.h"

MessageRepository::MessageRepository() {}
std::vector<MessageModel> MessageRepository::getMessagesForUser(const QString& field ,const int& id){
    QSqlQuery q;
    QString statement = "select * from messages where" + field + " = :id";
    q.prepare(statement);
    q.bindValue(":id", id);

    std::vector<MessageModel>msgs;
    if(!q.exec()){
        qDebug() << "Failed to retreive Messages";
        return msgs;
    }

    while(q.next()){
        QDateTime timestamp = q.value(1).toDateTime();
        QString content = q.value(2).toString();
        UserModel receiver = UserRepository::getUserFromId(q.value(3).toInt());

        msgs.push_back(MessageModel(receiver, content, timestamp));
    }

    return msgs;
}
std::vector<MessageModel> MessageRepository::getSentMessagesForUser(const int& id){
    return getMessagesForUser("sender_id", id);
}
std::vector<MessageModel> MessageRepository::getReceivedMessagesForUser(const int& id){
    return getMessagesForUser("receiver_id", id);
}
