#include "../../includes/db_manager.hpp"
#include <exception>
#include <iostream>
#include <iterator>
#include <pqxx/pqxx>

DatabaseManager::DatabaseManager():conn(nullptr){}
void DatabaseManager::connect_to_db(){
  
  try{
    conn = new pqxx::connection("dbname=terminet user=rgb password= host=localhost port=5432");

    if(conn->is_open())
      std::cout << "database connection succesfull\n";
    else
      std::cout << "cannot open database\n";
  } catch(std::exception &e) {
    std::cerr << e.what();
  }
}

void DatabaseManager::disconnect_db(){
  
  try {
    if(conn && conn->is_open()) {
      delete conn;
      conn = nullptr;
    }
    std::cout<< "Disconnect Succesfull\n";
  }catch(std::exception &e){
    std::cout << "Error while Disconnecting db : "<< e.what() << std::endl;
  }
}
