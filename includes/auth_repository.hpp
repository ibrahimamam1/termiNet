#include "db_manager.hpp"

class AuthenticationRepository{
  DatabaseManager db_instance;

public:
  AuthenticationRepository(DatabaseManager& db);
  void add_new_auth_entry();
};
