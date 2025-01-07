#include "login.h"
#include "signup.h"
#include "../helpers/api_client/apiclient.h"
#include "../helpers/hash_helper/hashhelper.h"
#include "../src/network/login/loginrepository.h"
#include "../src/network/user/user_repository.h"
#include "../helpers/apphelper.h"
#include "../src/helpers/validators/formvalidator.h"
#include "../src/common/type/types.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QScopedPointer>

Login::Login(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setupConnections();
}

Login::~Login() = default;

void Login::setupUI()
{
    mainContainer = new QHBoxLayout(this);
    loginContainer = new QVBoxLayout();
    formContainer = new QVBoxLayout();
    bottomContainer = new QVBoxLayout();

    // Setup Logo
    logo = new QLabel(this);
    logo->setPixmap(QPixmap(":/assets/logo.png"));

    // Setup Welcome Text
    welcomeText = new QLabel("Welcome Back!", this);
    QFont welcomeFont = welcomeText->font();
    welcomeFont.setPointSize(22);
    welcomeFont.setBold(true);
    welcomeText->setFont(welcomeFont);

    auto welcomeRow = new QHBoxLayout();
    welcomeRow->addWidget(logo);
    welcomeRow->addWidget(welcomeText);

    // Setup Form Fields
    emailField = new QLineEdit(this);
    emailField->setPlaceholderText("Enter Your Email");

    passwordField = new QLineEdit(this);
    passwordField->setPlaceholderText("Enter Password");
    passwordField->setEchoMode(QLineEdit::Password);

    //setup login button
    loginBtn = new QPushButton("Login", this);

    // Setup form Container
    formContainer->addWidget(emailField);
    formContainer->addWidget(passwordField);
    formContainer->addWidget(loginBtn);

    // Setup Forgot Password Label
    forgotPassword = new QLabel(this);
    forgotPassword->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Forgot Password?</a>");
    forgotPassword->setTextFormat(Qt::RichText);
    forgotPassword->setTextInteractionFlags(Qt::TextBrowserInteraction);

    // Setup Create Account Label
    createAccount = new QLabel(this);
    createAccount->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Create an Account</a>");
    createAccount->setTextFormat(Qt::RichText);
    createAccount->setTextInteractionFlags(Qt::TextBrowserInteraction);

    //setup bottom container(create account and forgot password)
    bottomContainer->addWidget(forgotPassword);
    bottomContainer->addWidget(createAccount);
    bottomContainer->addStretch();

    //setup socials
    divider = new DividerWidget(this);
    socials = new SocialsWidget(this);


    //setup login VLayout
    loginContainer->addStretch();
    loginContainer->addLayout(welcomeRow);
    loginContainer->addLayout(formContainer);
    loginContainer->addLayout(bottomContainer);
    loginContainer->addWidget(divider);
    loginContainer->addWidget(socials);
    loginContainer->addStretch();

    //setup main HLayout(centralise login VLayout)
    mainContainer->addStretch();
    mainContainer->addLayout(loginContainer);
    mainContainer->addStretch();

    setLayout(mainContainer);
    setMinimumSize(400, 600);
}

void Login::setupConnections()
{
    connect(loginBtn, &QPushButton::clicked, this, &Login::onLoginButtonClicked);
    connect(forgotPassword, &QLabel::linkActivated, this, &Login::onForgotPasswordClicked);
    connect(createAccount, &QLabel::linkActivated, this, &Login::onCreateAccountClicked);
    connect(socials, &SocialsWidget::googleLoginClicked, this, &Login::onGoogleLogin);
    connect(socials, &SocialsWidget::facebookLoginClicked, this, &Login::onFacebookLogin);
}

void Login::onLoginButtonClicked()
{
    QString email = emailField->text().trimmed();
    QString password = passwordField->text().trimmed();

    //Validate Form
    if(!FormValidator::validateEmailAddress(email)){
        QMessageBox::warning(this, "Input Error", "Invalid Email Address.");
        return;
    }

    QString hashedPassword = HashHelper::hashString(password);
    LoginResult loginResult = LoginRepository::login(email, hashedPassword);

    if (loginResult == LoginResult::SUCCESS) {
        UserModel user = UserRepository::getUserFromEmail(email);
        AuthenticatedUser::setInstance(user);
        AppHelper::saveUserForPersistentLogin(user.getId());
        emit loginSuccessful();
    } else if(loginResult == LoginResult::FAILED){
        QMessageBox::critical(this, "Login Failed", "Incorrect email or password. Please try again.");
    }else if(loginResult == LoginResult::SERVER_ERROR){
        QMessageBox::critical(this, "Server Error", "Please check your internet Connection or try later");
    }else{
        QMessageBox::critical(this, "Network Error", "Please check your internet Connection or try later");
    }
}

void Login::onGoogleLogin(){
    LoginResult login = LoginRepository::googleLogin();
    if(login == LoginResult::SUCCESS){
        UserModel user = UserRepository::getUserFromEmail("test@gmail.com");
        AuthenticatedUser::setInstance(user);
        AppHelper::saveUserForPersistentLogin(user.getId());
        emit loginSuccessful();
    }else if(login == LoginResult::FAILED){
        QMessageBox::critical(this, "Login Failed", "Incorrect email or password. Please try again.");
    }else if(login == LoginResult::SERVER_ERROR){
        QMessageBox::critical(this, "Server Error", "Please check your internet Connection or try later");
    }else{
        QMessageBox::critical(this, "Network Error", "Please check your internet Connection or try later");
    }
}

void Login::onFacebookLogin(){
    QMessageBox::warning(this, "Unavailable", "Service Currently Unavailable, please use google or email");
}

void Login::onForgotPasswordClicked()
{
    qDebug() << "Forgot password clicked";
    // TODO: Implement forgot password logic
}

void Login::onCreateAccountClicked()
{
    emit createAccountClicked();
}


