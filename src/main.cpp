#include <iostream>
#include "../includes/db_manager.hpp"
#include "../includes/user_repository.hpp"
#include <pqxx/pqxx>
int main (int argc, char *argv[]) {
  
  DatabaseManager *db = new DatabaseManager();
  UserRepository user_rep( db);
  if( !db->connect_to_db() ){
    std::cout << "Connection To database Failed";
    return 0;
  }

  db->create_schema();
  
  UserModel user1(1 , "iba", "iba@gmail.com", "compilers are cool", time(0));
  user_rep.add_new_user_entry(user1);
  db->disconnect_db();
  return 0;
}
