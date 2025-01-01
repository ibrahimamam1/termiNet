#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include "../../../src/models/user/usermodel.h"

class UserRepository
{
public:
    UserRepository();
    static bool addUserToDb(std::string name, std::string email, std::string sex, char* dob, std::string passwd, char* created_at);
    static void readUserFromDb();
    static UserModel getUserFromId(int id);
    static UserModel getUser(const QString& uri);
    static UserModel getUserFromEmail(const QString& email);
    static UserModel getUserFromName(const QString& name);

    //update functions
    static void updateUser(const QString& field, const QString& key);
    static void updateUserName(const QString &newName);
    static void updateUserEmail(const QString &newEmail);
    static void updateUserDob(const QString &newDob);
    static void updateUserBio(const QString &newBio);
    static void updateUserProfilePic(const QIcon &newProfilePic);
};

#endif // USER_REPOSITORY_H
