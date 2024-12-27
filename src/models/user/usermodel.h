#ifndef USERMODEL_H
#define USERMODEL_H
#include <QString>

class UserModel
{
private:
    unsigned int id;
    QString name;
    QString email;
    QString sex;
    QString dob;
    QString bio;
    QString created_at;


public:
    UserModel();
    UserModel(int u_id, QString u_name, QString u_email, QString u_sex, QString u_dob, QString u_bio, QString u_created_at);
    UserModel(const UserModel& user);

    // Getters
    unsigned int getId() const;
    QString getName() const;
    QString getEmail() const;
    QString getSex() const;
    QString getDob() const;
    QString getBio() const;
    QString getCreatedAt() const;

    // Setters
    void setId(unsigned int id);
    void setName(const QString &name);
    void setEmail(const QString &email);
    void setSex(const QString &sex);
    void setDob(const QString &dob);
    void setBio(const QString &bio);
    void setCreatedAt(const QString &created_at);
};

#endif // USERMODEL_H