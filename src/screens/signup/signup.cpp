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
    signUpContainer = new QVBoxLayout();
    signUpFormContainer = new QVBoxLayout();

    setupTitleText();
    setupFormFields();
    setupSignupButton();
    setupSocialsLogin();

    signUpContainer->addWidget(titleText);
    signUpContainer->addLayout(signUpFormContainer);
    signUpContainer->addWidget(divider);
    signUpContainer->addWidget(socials);

    // Create a centered layout for the first page
    auto firstPageCenteredInnerLayout = new QVBoxLayout();
    firstPageCenteredInnerLayout->addStretch();
    firstPageCenteredInnerLayout->addLayout(signUpContainer);
    firstPageCenteredInnerLayout->addStretch();
    firstPageCenteredInnerLayout->setAlignment(Qt::AlignCenter);

    auto firstPageCenteredOuterLayout = new QHBoxLayout();
    firstPageCenteredOuterLayout->addStretch();
    firstPageCenteredOuterLayout->addLayout(firstPageCenteredInnerLayout);
    firstPageCenteredOuterLayout->addStretch();
    firstPageCenteredOuterLayout->setAlignment(Qt::AlignCenter);


    //second page
    secondPageContainer = new QVBoxLayout();
    secondPageUserNameField = createFormField("Username", "Choose Your Username");
    auto dateLabel = new QLabel("Date Of Birth");
    secondPageDateOfBirthField = new QDateEdit(QDate::currentDate());
    finishButton = new QPushButton("Done");
    secondPageContainer->addStretch();
    secondPageContainer->addLayout(secondPageUserNameField);
    secondPageContainer->addWidget(dateLabel);
    secondPageContainer->addWidget(secondPageDateOfBirthField);
    secondPageContainer->addWidget(finishButton);
    secondPageContainer->addStretch();

    // Create a centered layout for the second page
    auto secondPageCenteredInnerLayout = new QVBoxLayout();
    secondPageCenteredInnerLayout->addStretch();
    secondPageCenteredInnerLayout->addLayout(secondPageContainer);
    secondPageCenteredInnerLayout->addStretch();
    secondPageCenteredInnerLayout->setAlignment(Qt::AlignCenter);
    auto secondPageCenteredOuterLayout = new QHBoxLayout();
    secondPageCenteredOuterLayout->addStretch();
    secondPageCenteredOuterLayout->addLayout(secondPageCenteredInnerLayout);
    secondPageCenteredOuterLayout->addStretch();
    secondPageCenteredOuterLayout->setAlignment(Qt::AlignCenter);


    //setup stacked widget
    pages = new QStackedWidget();

    auto page1 = new QWidget();
    page1->setLayout(firstPageCenteredOuterLayout);

    auto page2 = new QWidget();
    page2->setLayout(secondPageCenteredOuterLayout);

    pages->addWidget(page1);
    pages->addWidget(page2);

    auto pageLayout = new QVBoxLayout(this);
    pageLayout->addWidget(pages);
    this->setLayout(pageLayout);


    setWindowTitle("Sign Up");
    setMinimumWidth(400);
    setMinimumHeight(600);
}

void Signup::setupTitleText() {
    titleText = new QLabel("Hello, Let's create your termiNet Account!!");
    QFont titleFont = titleText->font();
    titleFont.setBold(true);
    titleFont.setPointSize(20);
    titleText->setFont(titleFont);
}

void Signup::setupFormFields() {
    userNameField = createFormField("Username", "Enter Your UserName");
    emailField = createFormField("Email", "Enter Your Email");
    dateOfBirthField = new QDateEdit(QDate::currentDate());
    dateOfBirthField->setDisplayFormat("dd/MM/yyyy");
    passwordField = createFormField("Password", "Enter Your Password", QLineEdit::Password);
    confirmPasswordField = createFormField("Confirm Password", "Confirm Your Password", QLineEdit::Password);

    signUpFormContainer->addLayout(userNameField);
    signUpFormContainer->addLayout(emailField);
    signUpFormContainer->addWidget(new QLabel("Date Of Birth"));
    signUpFormContainer->addWidget(dateOfBirthField);
    signUpFormContainer->addLayout(passwordField);
    signUpFormContainer->addLayout(confirmPasswordField);
}

QVBoxLayout* Signup::createFormField(const QString& labelText, const QString& placeholder, QLineEdit::EchoMode echoMode) {
    auto layout = new QVBoxLayout();
    auto label = new QLabel(labelText);
    auto field = new QLineEdit();
    field->setPlaceholderText(placeholder);
    field->setEchoMode(echoMode);

    // Store the reference when creating
    if (labelText == "Username") userNameInput = field;
    else if (labelText == "Email") emailInput = field;
    else if (labelText == "Password") passwordInput = field;
    else if (labelText == "Confirm Password") confirmPasswordInput = field;

    layout->addWidget(label);
    layout->addWidget(field);
    layout->addStretch(4);
    return layout;
}

void Signup::setupSignupButton() {
    signupBtn = new QPushButton("Create Account");
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
    QString name = userNameInput->text();
    QString email = emailInput->text();
    QDate dateOfBirth = dateOfBirthField->date();
    QString password = passwordInput->text();
    QString confirmPassword = confirmPasswordInput->text();

    QString errorMsg = validateSignupForm(name, email, dateOfBirth, password, confirmPassword);
    if (!errorMsg.isEmpty()) {
        QMessageBox::critical(this, "Validation Error", errorMsg, QMessageBox::Ok);
        return;
    }

    QString errorMessage = "";
    int errorCode = SignupRepository::createNewUserAccountWithEmailAndPassword(name, email, dateOfBirth, password, errorMessage);
    qDebug() << "Signup: Create New User account with email and password complete";
    if(errorCode){
        QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + errorMessage, QMessageBox::Ok);
    }else{
        QMessageBox::information(this, "Account Created", "Account Created Successfully\nEnjoy Sharing Your Ideas", QMessageBox::Ok);
        UserModel user = UserRepository::getUserFromEmail(email);
        AuthenticatedUser::setInstance(user);
        AppHelper::saveUserForPersistentLogin(user.getId());
        emit signupSuccessful();
    }
}



void Signup::onGoogleSignup(){
    GoogleReply reply = SignupRepository::googleSignup();

    QEventLoop loop;

    if(!reply.accessToken.isEmpty()){
        pages->setCurrentIndex(1);
        connect(finishButton, &QPushButton::clicked, this, [&](){
            QString name = userNameInput->text();
            QDate dob = secondPageDateOfBirthField->date();
            QString errorMsg = "";

            if (name.isEmpty()){
                QMessageBox::critical(this, "Validation Error", "User Name field cannot be left empty", QMessageBox::Ok);
                loop.quit();
                return;
            }

            if(!FormValidator::validateUserName(name, errorMsg)){
                QMessageBox::critical(this, "Validation Error", errorMsg, QMessageBox::Ok);
                loop.quit();
                return;
            }

            if (!dob.isValid()){
                QMessageBox::critical(this, "Validation Error", "Invalid Date of Birth", QMessageBox::Ok);
                loop.quit();
                return;
            }

            QString errorMessage;
            int error_code = SignupRepository::createNewUserAccountWithGoogle(name, dob, reply.idToken, errorMessage);
            if(error_code){
                QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + errorMessage, QMessageBox::Ok);
                loop.quit();
            }else{
                QMessageBox::information(this, "Account Created", "Account Created Successfully\nEnjoy Sharing Your Ideas", QMessageBox::Ok);
                UserModel user = UserRepository::getUserFromGoogleId(reply.idToken);
                AuthenticatedUser::setInstance(user);
                AppHelper::saveUserForPersistentLogin(user.getId());
                loop.quit();
                emit signupSuccessful();
            }

        });
        loop.exec();

    }

}

