#include "db_manager.hpp"
#include "models/user_model.hpp"
#include <string>
class UserRepository{
  DatabaseManager *db_instance;

public:
  UserRepository(DatabaseManager *db);
  bool is_user_already_in_db(std::string& email);
  void add_new_user_entry(UserModel& user);
};
