#include "authenticateduser.h"

AuthenticatedUser* AuthenticatedUser::instance = nullptr;

AuthenticatedUser::AuthenticatedUser(UserModel& user) : UserModel(user) {}

AuthenticatedUser* AuthenticatedUser::getInstance(){
    return instance;
}

void AuthenticatedUser::setInstance(UserModel& user){
    if(instance == nullptr){
        instance = new AuthenticatedUser(user);
    }

}
