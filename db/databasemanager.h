#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>

class DatabaseManager
{
    QSqlDatabase db;
public:
    DatabaseManager();
    bool connect();
    void disconnect();
    void create_schema();
    void delete_schema();

    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
