#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QSpacerItem>
#include<Qt>
#include<QFrame>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include"widgets/divider.h"
#include "widgets/socials.h"
#include "../src/models/user/usermodel.h"


class Login : public QDialog
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    QVBoxLayout *loginContainer;
    QVBoxLayout *formContainer;
    QVBoxLayout *bottomContainer;
    DividerWidget *divider;
    SocialsWidget *socials;
    QLabel *logo;
    QLabel *welcomeText;
    QLineEdit *emailField;
    QLineEdit *passwordField;
    QPushButton *loginBtn;
    QLabel *forgotPassword;
    QLabel *createAccount;

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void setupConnections();
    void setupUI();
signals:
    void loginSuccessful();
    void createAccountClicked();

private slots:
    void onLoginButtonClicked();
    void onGoogleLogin();
    void onFacebookLogin();
    void onForgotPasswordClicked();
    void onCreateAccountClicked();

};

#endif // LOGIN_H
