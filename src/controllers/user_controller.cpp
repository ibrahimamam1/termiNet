#include "../../includes/controllers/user_controller.hpp"
#include <iostream>
#include <string>

UserController::UserController(DatabaseManager *db){
  user_repo = new UserRepository(db);
}
void UserController::signup(UserModel& user){
  bool is_exist = user_repo->is_user_already_in_db(user.email);
  if(is_exist){
    std::cout << "Email Already Exist\n";
    return;
  }

  user_repo->add_new_user_entry(user);
  std::cout << "user Created succesfully\n";
}

