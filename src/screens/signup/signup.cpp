#include "signup.h"
#include "../../network/user/user_repository.h"
#include "../../../helpers/api_client/apiclient.h"
#include "../../../helpers/hash_helper/hashhelper.h"
#include "../../helpers/validators/formvalidator.h"
#include "../../../helpers/apphelper.h"
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
    mainContainer = new QHBoxLayout(this);
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
    setLayout(mainContainer);

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

    QJsonObject jsonData = createUserJson(name, email, dateOfBirth, password);
    sendSignupRequest(jsonData);
}

QJsonObject Signup::createUserJson(const QString& name, const QString& email, const QDate& dateOfBirth, const QString& password) {
    QJsonObject jsonData;
    jsonData["user_name"] = name;
    jsonData["user_email"] = email;
    jsonData["user_sex"] = "M"; // Default value
    jsonData["user_dob"] = dateOfBirth.toString("yyyy-MM-dd");
    jsonData["user_bio"] = "";
    jsonData["password"] = HashHelper::hashString(password);
    jsonData["created_at"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    return jsonData;
}

void Signup::sendSignupRequest(const QJsonObject& jsonData) {
    ApiClient& apiClient = ApiClient::getInstance();
    QString url = apiClient.getUserDataUrl();
    QNetworkReply* reply = apiClient.makePostRequest(url, jsonData, "");

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonObject responseJson = QJsonDocument::fromJson(reply->readAll()).object();
            if (responseJson.contains("Status") && responseJson["Status"].toString() == "Created") {
                QMessageBox::information(this, "Account Created", "Account Created Successfully\nEnjoy Sharing Your Ideas", QMessageBox::Ok);
                UserModel user = UserRepository::getUserFromEmail(jsonData["user_email"].toString());
                AuthenticatedUser::setInstance(user);
                AppHelper::saveUserForPersistentLogin(user.getId());
                emit signupSuccessful();
            } else {
                QString errorMessage = responseJson.contains("Message") ? responseJson["Message"].toString() : "Unknown error from server.";
                QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + errorMessage, QMessageBox::Ok);
            }
        } else {
            QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + reply->errorString(), QMessageBox::Ok);
        }
        reply->deleteLater();
    });
}
