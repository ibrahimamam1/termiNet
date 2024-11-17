#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class DatabaseManager
{
    QSqlDatabase db;
    static std::unique_ptr<DatabaseManager> instance;
public:
    DatabaseManager();
    static DatabaseManager* getInstance();
    bool connect();
    void disconnect();
    bool executeSqlFile(const QString path);

    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
