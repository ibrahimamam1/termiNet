#include "../../includes/user_repository.hpp"
#include <ctime>
#include <exception>
#include <iostream>

UserRepository::UserRepository(DatabaseManager *db) : db_instance(db) {}

void UserRepository::add_new_user_entry(UserModel &user) {

  std::cout << "Yahhooooo\n";;
  pqxx::work tx( *(db_instance->conn) );
  
  std::cout << "Initialised tx\n";

  // convert created_at from a time_t var to a postgres compatible type
  std::tm *ptm = std::localtime(&user.created_at);
  char date_string[11];
  strftime(date_string, sizeof(date_string), "%Y-%m-%d", ptm);
  
  std::cout << "Converted Time\n";
  try {
    tx.exec_params(
        "insert into users(user_id, user_name, email, bio, created_at) "
        "values($1, $2, $3, $4, $5)",
        user.user_id, user.user_name, user.email, user.bio, date_string);
    tx.commit();
    std::cout << "User Added Successfully\n";
  } catch (std::exception &e) {
    std::cerr << "Error Adding User : " << e.what() << std::endl;
  }
}
