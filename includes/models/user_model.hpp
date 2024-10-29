#include <ctime>
#include <string>
class UserModel{
public:

  int user_id;
  std::string user_name;
  std::string email;
  std::string bio;
  time_t created_at;

  UserModel(int uid , std::string name , std::string _email , std::string _bio , time_t _created_at) :user_id(uid), user_name(name) , email(_email), bio(_bio), created_at(_created_at) {}
};
