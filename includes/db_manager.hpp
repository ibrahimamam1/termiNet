#pragma once
#include <pqxx/pqxx>

class DatabaseManager{
public:
  pqxx::connection *conn;

  DatabaseManager();
  pqxx::connection& getConnection();
  bool connect_to_db();
  void disconnect_db();
  void create_schema();
  void delete_schema();
};
