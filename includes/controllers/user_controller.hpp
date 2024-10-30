#include <curl/curl.h>
#include <string>
#include "../user_repository.hpp"

class UserController{
  UserRepository *user_repo;  

  public:
  UserController(DatabaseManager *db);
  void signup(UserModel& user);
  void login(std::string username , std::string pass);
};
