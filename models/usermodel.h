#ifndef USERMODEL_H
#define USERMODEL_H
#include <string>

class UserModel
{
private:
    unsigned int id;
    std::string name;
    std::string email;
    std::string sex;
    std::string dob;
    std::string bio;
    std::string created_at;

    // Private Constructor
    UserModel();

    // Singleton instance
    static UserModel *instance;

public:
    // Public access to the singleton instance
    static UserModel *getInstance();

    // Deleted methods to avoid copies of the singleton
    UserModel(const UserModel &) = delete;
    UserModel &operator=(const UserModel &) = delete;

    // Getters
    unsigned int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getSex() const;
    std::string getDob() const;
    std::string getBio() const;
    std::string getCreatedAt() const;

    // Setters
    void setId(unsigned int id);
    void setName(const std::string &name);
    void setEmail(const std::string &email);
    void setSex(const std::string &sex);
    void setDob(const std::string &dob);
    void setBio(const std::string &bio);
    void setCreatedAt(const std::string &created_at);
};

#endif // USERMODEL_H
