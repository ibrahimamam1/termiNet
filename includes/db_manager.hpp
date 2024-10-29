#pragma once
#include <pqxx/pqxx>

class DatabaseManager{
  pqxx::connection *conn;

public:
  DatabaseManager();
  void connect_to_db();
  void disconnect_db();
};
