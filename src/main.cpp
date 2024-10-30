#include <iostream>
#include "../includes/db_manager.hpp"
#include "../includes/controllers/user_controller.hpp"
#include <pqxx/pqxx>
int main (int argc, char *argv[]) {
  
  DatabaseManager *db = new DatabaseManager();
  UserController user_controller( db);
  if( !db->connect_to_db() ){
    std::cout << "Connection To database Failed";
    return 0;
  }

  db->create_schema();
  
  UserModel user1(2 , "iba2", "iba2@gmail.com", "compilers are cool", time(0));
  std::cout << "User Model Created\n";

  user_controller.signup(user1);
  db->disconnect_db();
  return 0;
}
