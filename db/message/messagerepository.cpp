#include "messagerepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include "../user/user_repository.h"

MessageRepository::MessageRepository() {}
std::vector<MessageModel> MessageRepository::getMessagesForUser(int id){
    QSqlQuery q;
    q.prepare("select * from messages where sender_id = :id or receiver_id = :id");
    q.bindValue(":id", id);

    std::vector<MessageModel>msgs;
    if(!q.exec()){
        qDebug() << "Failed to retreive Messages";
        return msgs;
    }

    while(q.next()){
        UserModel sender = UserRepository::getUserFromId(q.value(1).toInt());
        UserModel receiver = UserRepository::getUserFromId(q.value(2).toInt());
        QString content = q.value(3).toString();
        QString preview = content;
        preview.chop(10);

        msgs.push_back(MessageModel(sender, receiver, preview, content));
    }

    return msgs;
}
