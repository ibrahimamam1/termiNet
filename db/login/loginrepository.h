#ifndef LOGINREPOSITORY_H
#define LOGINREPOSITORY_H
#include <QString>

class LoginRepository
{
public:
    LoginRepository();
    static bool login(const QString& email, const QString& password);
};

#endif // LOGINREPOSITORY_H
