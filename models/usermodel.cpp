#include "usermodel.h"

// Initialize the static instance to nullptr
UserModel *UserModel::instance = nullptr;

// Private constructor
UserModel::UserModel() : id(0), name(""), email(""), sex(""), dob(""), bio(""), created_at("") {}

// Public method to access the singleton instance
UserModel *UserModel::getInstance()
{
    if (instance == nullptr)
    {
        instance = new UserModel();
    }
    return instance;
}

// Getters
unsigned int UserModel::getId() const { return id; }
std::string UserModel::getName() const { return name; }
std::string UserModel::getEmail() const { return email; }
std::string UserModel::getSex() const { return sex; }
std::string UserModel::getDob() const { return dob; }
std::string UserModel::getBio() const { return bio; }
std::string UserModel::getCreatedAt() const { return created_at; }

// Setters
void UserModel::setId(unsigned int id) { this->id = id; }
void UserModel::setName(const std::string &name) { this->name = name; }
void UserModel::setEmail(const std::string &email) { this->email = email; }
void UserModel::setSex(const std::string &sex) { this->sex = sex; }
void UserModel::setDob(const std::string &dob) { this->dob = dob; }
void UserModel::setBio(const std::string &bio) { this->bio = bio; }
void UserModel::setCreatedAt(const std::string &created_at) { this->created_at = created_at; }
