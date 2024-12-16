#ifndef MESSAGEREPOSITORY_H
#define MESSAGEREPOSITORY_H

#include<vector>
#include "../../models/message/messagemodel.h"

class MessageRepository
{
public:
    MessageRepository();
    static std::vector<MessageModel>getMessagesForUser(int id);
};

#endif // MESSAGEREPOSITORY_H
