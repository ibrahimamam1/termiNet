#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H
#include<string>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>

class UserRepository
{
public:
    UserRepository();
    static void addUserToDb(std::string name, std::string email, std::string sex, char* dob, char* created_at);
    static void readUserFromDb();
};

#endif // USER_REPOSITORY_H
