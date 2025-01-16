#ifndef LOGINREPOSITORY_H
#define LOGINREPOSITORY_H
#include <QString>
#include "../../common/type/types.h"

class LoginRepository
{
public:
    LoginRepository();
    static LoginResult login(const QString& email, const QString& password);
    static LoginResult googleLogin(QString& googleId);
};

#endif // LOGINREPOSITORY_H
