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
    static UserModel getUserFromId(const QString& id);
    static UserModel getUser(const QString& uri);
    static UserModel getUserFromEmail(const QString& email);
    static UserModel getUserFromName(const QString& name);
    static UserModel getUserFromGoogleId(const QString& googleId);

    //update functions
    static bool updateUser(const QString& field, const QString& key);
    static bool updateUserName(const QString &newName);
    static bool updateUserEmail(const QString &newEmail);
    static bool updateUserDob(const QString &newDob);
    static bool updateUserBio(const QString &newBio);
    static bool updateUserProfilePic(const QIcon &newProfilePic);

};

#endif // USER_REPOSITORY_H
