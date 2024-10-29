#include "../../includes/db_manager.hpp"
#include <exception>
#include <iostream>
#include <iterator>
#include <ostream>
#include <pqxx/pqxx>
#include <stdexcept>

DatabaseManager::DatabaseManager():conn(nullptr){}
bool DatabaseManager::connect_to_db(){
  
  try{
    conn = new pqxx::connection("dbname=terminet user=rgb password= host=localhost port=5432");

    if(conn->is_open())
      return true;
      
    return false;
  } catch(std::exception &e) {
    std::cerr << "Error Occured While Connecting to db : " << e.what() << std::endl;
    return false;
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

void DatabaseManager::create_schema(){
  pqxx::work tx(*conn);

  tx.exec(
    "create table if not exists users("
      "user_id integer primary key,"
      "user_name text,"
      "email text,"
      "bio text,"
      "created_at date"
  ");"
);
  tx.exec(
     "create table if not exists threads("
    "thread_id integer primary key,"
    "title varchar(200) not null,"
    "content text,"
    "created_at date,"
    "author_id integer not null,"
    "community_id integer,"
    "parent_thread_id integer"
    ");"
  );

  tx.exec(
     "create table if not exists communities("
    "community_id integer primary key,"
    "name varchar(50) not null,"
    "description text,"
    "created_at date"
    ");"
  );

  tx.commit();
  std::cout<< "Schema Succesfully created\n";
}

void DatabaseManager::delete_schema(){
  pqxx::work tx(*conn);
  tx.exec(
    "drop table users;"
  );
   tx.exec(
    "drop table threads;"
  );
tx.exec(
    "drop table communities;"
  );

tx.commit();
std::cout<<"Schema Deleted Successfully\n";
}
