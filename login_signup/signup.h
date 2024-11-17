#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QFont>
#include "widgets/divider.h"
#include "widgets/socials.h"
#include "../db/databasemanager.h"

class Signup : public QDialog
{
    Q_OBJECT
    DatabaseManager *db;
    QHBoxLayout *mainContainer;
    QVBoxLayout *signUpContainer;
    QVBoxLayout *signUpFormContainer;
    QLabel *titleText;
    QVBoxLayout *userNameBox;
    QLabel *userNameLabel;
    QLineEdit *userNameField;
    QVBoxLayout *emailBox;
    QLabel *emailLabel;
    QLineEdit *emailField;
    QVBoxLayout *dateOfBirthBox;
    QLabel *dobLabel;
    QLineEdit *dobField;
    QVBoxLayout *paswordBox;
    QLabel *passwordLabel;
    QLineEdit *passwordField;
    QVBoxLayout *comfirmPasswordBox;
    QLabel *comfirmPasswordLabel;
    QLineEdit *comfirmPasswordField;
    QPushButton *signupBtn;
    DividerWidget *divider;
    SocialsWidget *socials;


public:
   explicit Signup(QWidget *parent = nullptr);
    bool validate_signup_form(std::string name ,std::string email ,std::string sex ,std::string dob ,std::string pass,std::string pass2);
   void readUserTable();
   ~Signup();

private slots:
    void on_create_account_btn_clicked();


};

#endif // SIGNUP_H
