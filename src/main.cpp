#include <iostream>
#include "../includes/db_manager.hpp"

int main (int argc, char *argv[]) {
  
  DatabaseManager *db = new DatabaseManager();

  db->connect_to_db();

  db->disconnect_db();
  return 0;
}
