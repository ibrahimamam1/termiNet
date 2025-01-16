#ifndef SIGNUP_REPOSITORY_H
#define SIGNUP_REPOSITORY_H
#include "../../common/type/types.h"

class SignupRepository
{
public:
    SignupRepository();
    static int createNewUserAccount(const QJsonObject& jsonData, QString& error_msg);
    static int createNewUserAccountWithEmailAndPassword(const QString& name, const QString& email, const QDate& dateOfBirth, const QString& password, QString& error_msg);
    static int createNewUserAccountWithGoogle(const QString& name, const QString& email, const QDate& dob, const QString& googleId, QString& error_msg);
    static const GoogleReply googleSignup();


};

#endif // SIGNUP_REPOSITORY_H
