#include "databasemanager.h"

DatabaseManager::DatabaseManager(){}


bool DatabaseManager::connect(){
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("terminet");
    db.setUserName("rgb");
    db.setPassword("");

    return db.open();
}

void DatabaseManager::create_schema(){
    QSqlQuery q;

    q.exec(
        "create table if not exists users("
        "user_id integer primary key,"
        "user_name text,"
        "user_email text,"
        "user_sex text,"
        "user_dob date,"
        "user_bio text,"
        "created_at date"
        ");"
        );
    q.exec(
        "create table if not exists threads("
        "thread_id integer primary key,"
        "title varchar(200) not null,"
        "content text,"
        "created_at date,"
        "author_id integer not null,"
        "community_id integer,"
        "parent_thread_id integer"
        ");"
        );

    q.exec(
        "create table if not exists communities("
        "community_id integer primary key,"
        "name varchar(50) not null,"
        "description text,"
        "created_at date"
        ");"
        );

    qDebug()<< "Schema Succesfully created\n";
}

void DatabaseManager::delete_schema(){
    QSqlQuery q;
    q.exec("drop table users");
    q.exec("drop table threads");
    q.exec("drop table communities");
}
DatabaseManager::~DatabaseManager(){
    db.close();
}
