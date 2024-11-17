#include "databasemanager.h"

std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;
DatabaseManager::DatabaseManager(){}

DatabaseManager* DatabaseManager::getInstance(){
    if(instance == nullptr){
        instance = std::unique_ptr<DatabaseManager>(new DatabaseManager());
    }
    return instance.get();
}


bool DatabaseManager::connect(){
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("terminet");
    db.setUserName("rgb");
    db.setPassword("");

    return db.open();
}

bool DatabaseManager::executeSqlFile(const QString path){
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Failed to open file\n";
        return false;
    }

    QTextStream in(&file);
    QString sqlQuery;
    QSqlQuery query;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith("--")) {
            continue; // Ignore empty lines and comments
        }
        sqlQuery += line;
        if (line.endsWith(";")) {
            // Execute the SQL command and clear for the next command
            sqlQuery.chop(1);  // Remove the trailing semicolon for QSqlQuery
            if (!query.exec(sqlQuery)) {
                qDebug() << "SQL execution error:" << query.lastError().text();
                return false;
            }
            sqlQuery.clear();
        }
    }
    file.close();
    return true;
}


DatabaseManager::~DatabaseManager(){
    db.close();
}
