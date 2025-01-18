#ifndef AUTHENTICATEDUSER_H
#define AUTHENTICATEDUSER_H
#include "usermodel.h"

class AuthenticatedUser : public UserModel{
    static std::unique_ptr<AuthenticatedUser> instance;
    AuthenticatedUser(UserModel& user);

public:
    static AuthenticatedUser& getInstance();
    static void setInstance(UserModel& user);

    friend class AuthenticatedUserFactory;
};

class AuthenticatedUserFactory{
public:
    static std::unique_ptr<AuthenticatedUser> create(UserModel& user)
    {
        return std::unique_ptr<AuthenticatedUser>(new AuthenticatedUser(user));
    }
};

#endif // AUTHENTICATEDUSER_H
