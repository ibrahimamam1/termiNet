#pragma once
#include <pqxx/pqxx>

class DatabaseManager{
  pqxx::connection *conn;

public:
  DatabaseManager();
  bool connect_to_db();
  void disconnect_db();
  void create_schema();
  void delete_schema();
};
