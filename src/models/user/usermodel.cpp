#include "usermodel.h"

UserModel::UserModel() : id(0), name(""), email(""), sex(""), dob(""), bio(""), created_at("") {}
UserModel::UserModel(int u_id, QString u_name, QString u_email, QString u_sex, QString u_dob, QString u_bio, QString u_created_at, const QIcon& u_profilePic) :
    id(u_id), name(u_name), email(u_email), sex(u_sex), dob(u_dob), bio(u_bio), created_at(u_created_at), profilePic(u_profilePic)
{}
UserModel::UserModel(const UserModel& user) {
    id = user.id;
    name = user.name;
    email = user.email;
    sex = user.sex;
    dob = user.dob;
    bio = user.bio;
    created_at = user.created_at;
    profilePic = user.profilePic;
}


// Getters
unsigned int UserModel::getId() const { return id; }
QString UserModel::getName() const { return name; }
QString UserModel::getEmail() const { return email; }
QString UserModel::getSex() const { return sex; }
QString UserModel::getDob() const { return dob; }
QString UserModel::getBio() const { return bio; }
QString UserModel::getCreatedAt() const { return created_at; }
QIcon UserModel::getProfilePic() const {return profilePic; }

// Setters
void UserModel::setId(unsigned int id) { this->id = id; }
void UserModel::setName(const QString &name) { this->name = name; }
void UserModel::setEmail(const QString &email) { this->email = email; }
void UserModel::setSex(const QString &sex) { this->sex = sex; }
void UserModel::setDob(const QString &dob) { this->dob = dob; }
void UserModel::setBio(const QString &bio) { this->bio = bio; }
void UserModel::setCreatedAt(const QString &created_at) { this->created_at = created_at; }
void UserModel::setProfilePic(const QIcon& pic){ this->profilePic = pic; }
