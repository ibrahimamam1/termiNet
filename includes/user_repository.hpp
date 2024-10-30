#include "db_manager.hpp"
#include "models/user_model.hpp"
class UserRepository{
  DatabaseManager *db_instance;

public:
  UserRepository(DatabaseManager *db);
  void add_new_user_entry(UserModel& user);
};
