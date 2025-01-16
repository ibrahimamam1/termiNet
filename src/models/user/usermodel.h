#ifndef USERMODEL_H
#define USERMODEL_H
#include <QString>
#include <QIcon>

class UserModel
{
private:
    QString id;
    QString name;
    QString email;
    QString sex;
    QString dob;
    QString bio;
    QString created_at;
    QIcon profilePic;


public:
    UserModel();
    UserModel(const QString& u_id, const QString& u_name, const QString& u_email, const QString& u_sex,
              const QString& u_dob, const QString& u_bio, const QString& u_created_at, const QIcon& u_profilePic);
    UserModel(const UserModel& user);

    // Getters
    QString getId() const;
    QString getName() const;
    QString getEmail() const;
    QString getSex() const;
    QString getDob() const;
    QString getBio() const;
    QString getCreatedAt() const;
    QIcon getProfilePic() const;

    // Setters
    void setId(const QString& id);
    void setName(const QString &name);
    void setEmail(const QString &email);
    void setSex(const QString &sex);
    void setDob(const QString &dob);
    void setBio(const QString &bio);
    void setCreatedAt(const QString &created_at);
    void setProfilePic(const QIcon& pic);
};

#endif // USERMODEL_H
