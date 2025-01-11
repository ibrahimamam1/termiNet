#include "signup.h"
#include "../../network/user/user_repository.h"
#include "../../../helpers/api_client/apiclient.h"
#include "../../../helpers/hash_helper/hashhelper.h"
#include "../../helpers/validators/formvalidator.h"
#include "../../../helpers/apphelper.h"
#include "../../network/signup/signup_repository.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QMessageBox>
#include <QDateEdit>

Signup::Signup(QWidget *parent) : QDialog(parent) {
    setupUI();
}

Signup::~Signup() {}

void Signup::setupUI() {
    //first page
    mainContainer = new QHBoxLayout();
    signUpContainer = new QVBoxLayout();
    signUpFormContainer = new QVBoxLayout();

    setupTitleText();
    setupFormFields();
    setupSignupButton();
    setupSocialsLogin();

    signUpContainer->addWidget(titleText, 1);
    signUpContainer->addLayout(signUpFormContainer, 5);
    signUpContainer->addWidget(divider, 1);
    signUpContainer->addWidget(socials, 1);

    mainContainer->addStretch(4);
    mainContainer->addLayout(signUpContainer, 2);
    mainContainer->addStretch(4);


    //second page
    secondPageContainer = new QVBoxLayout();
    secondPageUserNameField = createFormField("User Name", "Enter Your Username");
    secondPageDateOfBirthField = new QDateEdit(QDate::currentDate(), this);
    finishButton = new QPushButton("Done");


    //setup stacked widget
    pages = new QStackedWidget(this);

    auto page1 = new QWidget(this);
    page1->setLayout(mainContainer);

    auto page2 = new QWidget(this);
    page2->setLayout(secondPageContainer);

    pages->addWidget(page1);
    pages->addWidget(page2);

    setWindowTitle("Sign Up");
    setMinimumWidth(400);
    setMinimumHeight(600);
}

void Signup::setupTitleText() {
    titleText = new QLabel("Hello, Let's create your termiNet Account!!", this);
    QFont titleFont = titleText->font();
    titleFont.setBold(true);
    titleFont.setPointSize(20);
    titleText->setFont(titleFont);
}

void Signup::setupFormFields() {
    userNameField = createFormField("UserName", "Enter Your UserName");
    emailField = createFormField("Email", "Enter Your Email");
    dateOfBirthField = new QDateEdit(QDate::currentDate(), this);
    dateOfBirthField->setDisplayFormat("dd/MM/yyyy");
    passwordField = createFormField("Password", "Enter Your Password", QLineEdit::Password);
    confirmPasswordField = createFormField("Confirm Password", "Confirm Your Password", QLineEdit::Password);

    signUpFormContainer->addLayout(userNameField);
    signUpFormContainer->addLayout(emailField);
    signUpFormContainer->addWidget(new QLabel("Date Of Birth", this));
    signUpFormContainer->addWidget(dateOfBirthField);
    signUpFormContainer->addLayout(passwordField);
    signUpFormContainer->addLayout(confirmPasswordField);
}

QVBoxLayout* Signup::createFormField(const QString& labelText, const QString& placeholder, QLineEdit::EchoMode echoMode) {
    auto layout = new QVBoxLayout();
    auto label = new QLabel(labelText, this);
    auto field = new QLineEdit(this);
    field->setPlaceholderText(placeholder);
    field->setEchoMode(echoMode);
    layout->addWidget(label);
    layout->addWidget(field);
    layout->addStretch(4);
    return layout;
}

void Signup::setupSignupButton() {
    signupBtn = new QPushButton("Create Account", this);
    connect(signupBtn, &QPushButton::clicked, this, &Signup::onCreateAccountBtnClicked);
    signUpFormContainer->addWidget(signupBtn, 1);
    signUpFormContainer->addStretch(4);
}

void Signup::setupSocialsLogin() {
    divider = new DividerWidget();
    socials = new SocialsWidget();
    connect(socials, &SocialsWidget::googleLoginClicked, this, &Signup::onGoogleSignup);
}

QString Signup::validateSignupForm(const QString& name, const QString& email, const QDate& dateOfBirth,
                                   const QString& password, const QString& confirmPassword) {

    QString error_msg;

    if (name.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty())
        return "Fields cannot be left empty\n";

    if(!FormValidator::validateUserName(name, error_msg))
        return error_msg;

    if (!FormValidator::validateEmailAddress(email))
        return "Invalid Email address\n";

    if (!dateOfBirth.isValid())
        return "Invalid Date of Birth\n";

    if (!FormValidator::validatePassword(password, error_msg))
        return error_msg;

    if (password != confirmPassword)
        return "Passwords do not match. Please confirm your password\n";

    return "";
}

void Signup::onCreateAccountBtnClicked() {

    QString name = userNameField->findChild<QLineEdit*>()->text();
    QString email = emailField->findChild<QLineEdit*>()->text();
    QDate dateOfBirth = dateOfBirthField->date();
    QString password = passwordField->findChild<QLineEdit*>()->text();
    QString confirmPassword = confirmPasswordField->findChild<QLineEdit*>()->text();

    QString errorMsg = validateSignupForm(name, email, dateOfBirth, password, confirmPassword);
    if (!errorMsg.isEmpty()) {
        QMessageBox::critical(this, "Validation Error", errorMsg, QMessageBox::Ok);
        return;
    }

    int error_code = SignupRepository::createNewUserAccountWithEmailAndPassword(name, email, dateOfBirth, password, error_message);
    if(error_code){
        QString errorMessage = responseJson.contains("Message") ? responseJson["Message"].toString() : "Unknown error from server.";
        QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + errorMessage, QMessageBox::Ok);
    }else{
        QMessageBox::information(this, "Account Created", "Account Created Successfully\nEnjoy Sharing Your Ideas", QMessageBox::Ok);
        UserModel user = UserRepository::getUserFromEmail(jsonData["user_email"].toString());
        AuthenticatedUser::setInstance(user);
        AppHelper::saveUserForPersistentLogin(user.getId());
        emit signupSuccessful();
    }
}



void Signup::onGoogleSignup(){
    qDebug() << "Signup: Will initiate signup";
    GoogleReply reply = SignupRepository::googleSignup();
    if(!reply.accessToken.isEmpty()){
        pages->setCurrentIndex(1);
        connect(finishButton, &QPushButton::clicked, this, [&], {
            QString name = secondPageUserNameField->findChild<QLineEdit*>()->text();
            QDateTime dob = secondPageDateOfBirthField->date();
            QString error_msg;

            if (name.isEmpty()){
                QMessageBox::critical(this, "Validation Error", "User Name field cannot be left empty", QMessageBox::Ok);
                return;
            }

            if(!FormValidator::validateUserName(name, error_msg)){
                QMessageBox::critical(this, "Validation Error", errorMsg, QMessageBox::Ok);
                return;
            }

            if (!dateOfBirth.isValid()){
                QMessageBox::critical(this, "Validation Error", "Invalid Date of Birth", QMessageBox::Ok);
                return;
            }

            int error_code = SignupRepository::createNewUserAccountWithGoogle(name, "", dob, reply.idToken, error_message);
            if(error_code){
                QString errorMessage = responseJson.contains("Message") ? responseJson["Message"].toString() : "Unknown error from server.";
                QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + errorMessage, QMessageBox::Ok);
            }else{
                QMessageBox::information(this, "Account Created", "Account Created Successfully\nEnjoy Sharing Your Ideas", QMessageBox::Ok);
                UserModel user = UserRepository::getUserFromGoogleId(reply.idToken);
                AuthenticatedUser::setInstance(user);
                AppHelper::saveUserForPersistentLogin(user.getId());
                emit signupSuccessful();
            }

        });
    }

}

