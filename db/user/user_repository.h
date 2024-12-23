#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include "../../models/user/usermodel.h"

class UserRepository
{
public:
    UserRepository();
    static bool addUserToDb(std::string name, std::string email, std::string sex, char* dob, std::string passwd, char* created_at);
    static void readUserFromDb();
    static UserModel getUserFromId(int id);
    static UserModel getUserFromEmail(QString email);
    static UserModel getUserFromName(QString name);
};

#endif // USER_REPOSITORY_H
