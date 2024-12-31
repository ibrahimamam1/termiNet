#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "../../models/message/messagemodel.h"

class DatabaseManager
{
    QSqlDatabase db;
    static std::unique_ptr<DatabaseManager> instance;
public:
    DatabaseManager();
    static DatabaseManager& getInstance();
    static bool init();
    bool connect();
    void disconnect();
    bool executeSqlFile(const QString& path);
    bool addOutgoingMessage(const MessageModel& msg);
     bool addIncomingMessage(const MessageModel& msg);
    bool createSchema();

    std::vector<MessageModel>getSentMessagesTo(int id);
    std::vector<MessageModel>getReceivedMessagesFrom(int id) ;
    std::vector<MessageModel>getAllConversations();

    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
