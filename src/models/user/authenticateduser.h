#ifndef AUTHENTICATEDUSER_H
#define AUTHENTICATEDUSER_H
#include "usermodel.h"

class AuthenticatedUser : public UserModel
{
    static AuthenticatedUser* instance;
    AuthenticatedUser();
    AuthenticatedUser(UserModel& user);

public:
    static AuthenticatedUser* getInstance();
    static void setInstance(UserModel& user);
};

#endif // AUTHENTICATEDUSER_H
