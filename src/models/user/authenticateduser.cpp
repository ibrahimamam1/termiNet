#include "authenticateduser.h"

std::unique_ptr<AuthenticatedUser> AuthenticatedUser::instance = nullptr;

AuthenticatedUser::AuthenticatedUser(UserModel& user) : UserModel(user) {}

AuthenticatedUser& AuthenticatedUser::getInstance(){
    if(instance == nullptr){
        throw std::runtime_error("Instance not initialized. Call setInstance first.");
    }
    return *instance;
}

void AuthenticatedUser::setInstance(UserModel& user){
    if(instance == nullptr){
        instance = AuthenticatedUserFactory::create(user);
    }

}
