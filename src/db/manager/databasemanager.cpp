#include "databasemanager.h"
#include "../../models/message/messagemodel.h"
#include "../../network/user/user_repository.h"
#include <QStandardPaths>
#include <QDir>

std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;
DatabaseManager::DatabaseManager(){}

DatabaseManager& DatabaseManager::getInstance(){
    return *instance;
}
bool DatabaseManager::init(){
    if(instance == nullptr){
        instance = std::unique_ptr<DatabaseManager>(new DatabaseManager());
    }
    if(!instance->connect()){
        qDebug() << "Failed to connect to database";
        return false;
    }
    if(!instance->createSchema()){
        qDebug() << "Failed to Create Schema";
        return false;
    }
    return true;
}

bool DatabaseManager::connect() {
    QString dbLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/terminet/";
    if (dbLocation.isEmpty()) {
        qWarning() << "Could not determine writable application data location.";
        return false;
    }

    // Create the directory if it doesn't exist
    QDir dbDir(dbLocation);
    if (!dbDir.exists()) {
        if (!dbDir.mkpath(".")) {
            qWarning() << "Failed to create database directory.";
            return false;
        }
    }

    QString dbPath = dbLocation + "messages.db";

    // Use QSqlDatabase::database() to get or create a named connection
    if (!QSqlDatabase::contains("main_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE", "main_connection");
        db.setDatabaseName(dbPath);
    } else {
        db = QSqlDatabase::database("main_connection");
    }

    return db.open();
}

bool DatabaseManager::createSchema() {
    if(!db.open()){
        qDebug() << "Failed to connect to database";
        return false;
    }

    QSqlQuery query(db);

    QString createSentMessagesTable = R"(
        create table if not exists sent_messages(
        message_id integer primary key autoincrement,
        timestamp datetime,
        message_text text,
        recipient_id integer
        );
    )";

    if (!query.exec(createSentMessagesTable)) {
        qDebug() << "Error creating sent_messages table:" << query.lastError().text();
        return false;
    }

    QString createReceivedMessagesTable = R"(
        create table if not exists received_messages(
            message_id integer primary key autoincrement,
            timestamp datetime,
            message_text text,
            sender_id integer
        );

    )";
    if (!query.exec(createReceivedMessagesTable)) {
        qDebug() << "Error creating sent_messages table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::addOutgoingMessage(const MessageModel& msg){
    if(!db.open()){
        qDebug() << "Failed to conenct to database\n";
        return false;
    }

    QSqlQuery q(db);
    q.prepare("INSERT INTO sent_messages(timestamp, message_text, recipient_id) values (:time_s, :content, :id);");
    q.bindValue(":time_s", msg.getTimestamp());
    q.bindValue(":content", msg.getMessageContent());
    q.bindValue(":id", msg.getReceiver().getId());

    if(!q.exec()){
        qDebug() << "Failed to execute Query\nError : "<< q.lastError().text();
        return false;
    }
    return true;
}

std::vector<MessageModel> DatabaseManager::getSentMessagesTo(int id){
    std::vector<MessageModel>msgs;

    if(!db.open()){
        qDebug() << "Failed to conenct to database\n";
        return msgs;
    }

    QSqlQuery q(db);
    q.prepare("SELECT * from sent_messages where recipient_id = :r_id");
    q.bindValue(":r_id",id);


    if(!q.exec()){
        qDebug() << "Failed to retreived messages\nError: "<< q.lastError().text();
        return msgs;
    }
    while(q.next()){
        UserModel receiver = UserRepository::getUserFromId(q.value(3).toInt());
        QString content = q.value(2).toString();
        QDateTime time = q.value(3).toDateTime();
        msgs.push_back(MessageModel(receiver , content, time));
    }
    return msgs;
}

std::vector<MessageModel> DatabaseManager::getReceivedMessagesFrom(int id){
    std::vector<MessageModel>msgs;

    if(!db.open()){
        qDebug() << "Failed to conenct to database\n";
        return msgs;
    }

    QSqlQuery q(db);
    q.prepare("SELECT * from received_messages where sender_id = :s_id");
    q.bindValue(":s_id",id);


    if(!q.exec()){
        qDebug() << "Failed to retreived messages\nError: "<<q.lastError().text();
        return msgs;
    }
    while(q.next()){
        UserModel receiver = UserRepository::getUserFromId(q.value(3).toInt());
        QString content = q.value(2).toString();
        QDateTime time = q.value(3).toDateTime();
        msgs.push_back(MessageModel(receiver , content, time));
    }
    return msgs;
}

DatabaseManager::~DatabaseManager(){
    db.close();
}
