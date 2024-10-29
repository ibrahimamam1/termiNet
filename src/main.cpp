#include <iostream>
#include "../includes/db_manager.hpp"
#include <pqxx/pqxx>
int main (int argc, char *argv[]) {
  
  DatabaseManager *db = new DatabaseManager();

  if( !db->connect_to_db() ){
    std::cout << "Connection To database Failed";
    return 0;
  }

  db->create_schema();
  
    
  db->disconnect_db();
  return 0;
}
