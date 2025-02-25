#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QFont>
#include <QStackedWidget>
#include "../../common/widgets/divider.h"
#include "../../common/widgets/socials_widget.h"
#include "../../../home/home.h"

class Signup : public QDialog
{
    Q_OBJECT
    QStackedWidget *pages;
    QVBoxLayout *signUpContainer;
    QVBoxLayout *signUpFormContainer;
    QLabel *titleText;
    QLineEdit* userNameInput;
    QLineEdit* secondPageUserNameInput;
    QLineEdit* emailInput;
    QLineEdit* passwordInput;
    QLineEdit* confirmPasswordInput;
    QVBoxLayout *userNameField;
    QVBoxLayout *emailField;
    QDateEdit* dateOfBirthField;
    QVBoxLayout *passwordField;
    QVBoxLayout *confirmPasswordField;
    QPushButton *signupBtn;
    DividerWidget *divider;
    SocialsWidget *socials;

    QVBoxLayout *secondPageContainer;
    QVBoxLayout *secondPageUserNameField;
    QDateEdit *secondPageDateOfBirthField;
    QPushButton *finishButton;

public:
    explicit Signup(QWidget *parent = nullptr);
    void setupUI();
    void setupTitleText();
    void setupFormFields();
    QVBoxLayout* createFormField(const QString& labelText, const QString& placeholder, QLineEdit::EchoMode echoMode = QLineEdit::Normal);
    void setupSignupButton();
    void setupSocialsLogin();
    QString validateSignupForm(const QString& name, const QString& email,const QDate& dob, const QString& pass, const QString& pass2);
    QJsonObject createUserJson(const QString& name, const QString& email, const QDate& dateOfBirth, const QString& password);
    void sendSignupRequest(const QJsonObject& jsonData);
    ~Signup();
signals:
    void signupSuccessful();
private slots:
    void onCreateAccountBtnClicked();
    void onGoogleSignup();


};

#endif // SIGNUP_H
