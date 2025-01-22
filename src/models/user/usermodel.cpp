#include "usermodel.h"

UserModel::UserModel() : id(""), name(""), email(""), dob(QDate()), bio(""), created_at("") {}
UserModel::UserModel(const QString& u_id, const QString& u_name,
                     const QString& u_email, const QDate& u_dob,
                     const QString& u_bio, const QString& u_created_at,
                     const QIcon& u_profilePic) :
    id(u_id), name(u_name), email(u_email), dob(u_dob), bio(u_bio), created_at(u_created_at), profilePic(u_profilePic)
{}
UserModel::UserModel(const UserModel& user) {
    id = user.id;
    name = user.name;
    email = user.email;
    dob = user.dob;
    bio = user.bio;
    created_at = user.created_at;
    profilePic = user.profilePic;
}


// Getters
QString UserModel::getId() const { return id; }
QString UserModel::getName() const { return name; }
QString UserModel::getEmail() const { return email; }
QDate UserModel::getDob() const { return dob; }
QString UserModel::getBio() const { return bio; }
QString UserModel::getCreatedAt() const { return created_at; }
QIcon UserModel::getProfilePic() const {return profilePic; }

// Setters
void UserModel::setId(const QString& id) { this->id = id; }
void UserModel::setName(const QString &name) { this->name = name; }
void UserModel::setEmail(const QString &email) { this->email = email; }
void UserModel::setDob(const QDate &dob) { this->dob = dob; }
void UserModel::setBio(const QString &bio) { this->bio = bio; }
void UserModel::setCreatedAt(const QString &created_at) { this->created_at = created_at; }
void UserModel::setProfilePic(const QIcon& pic){ this->profilePic = pic; }
