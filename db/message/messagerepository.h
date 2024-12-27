#ifndef MESSAGEREPOSITORY_H
#define MESSAGEREPOSITORY_H

#include<vector>
#include "../../src/models/message/messagemodel.h"

class MessageRepository
{
public:
    MessageRepository();
    static std::vector<MessageModel> getSentMessagesForUser(const int& id);
    static std::vector<MessageModel> getReceivedMessagesForUser(const int& id);

private:
    static std::vector<MessageModel> getMessagesForUser(const QString& field ,const int& id);
};

#endif // MESSAGEREPOSITORY_H
