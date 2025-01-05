#include "signup.h"
#include "../src/network/user/user_repository.h"
#include "../helpers/api_client/apiclient.h"
#include "../helpers/hash_helper/hashhelper.h"
#include "../src/helpers/validators/formvalidator.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<cctype>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>

Signup::Signup(QWidget *parent) : QDialog(parent)
{
    mainContainer = new QHBoxLayout(this);
    signUpContainer = new QVBoxLayout();
    signUpFormContainer = new QVBoxLayout();
    titleText = new QLabel(this);
    userNameBox = new QVBoxLayout();
    userNameLabel = new QLabel(this);
    userNameField = new QLineEdit(this);
    emailBox = new QVBoxLayout();
    emailLabel = new QLabel(this);
    emailField = new QLineEdit(this);
    dateOfBirthBox = new QVBoxLayout();
    dobLabel = new QLabel(this);
    dobField = new QLineEdit(this);
    paswordBox = new QVBoxLayout();
    passwordLabel = new QLabel(this);
    passwordField = new QLineEdit(this);
    comfirmPasswordBox = new QVBoxLayout();
    comfirmPasswordLabel = new QLabel(this);
    comfirmPasswordField = new QLineEdit(this);
    signupBtn = new QPushButton(this);
    divider = new DividerWidget(this);
    socials = new SocialsWidget(this);

    //setup title text
    QFont titleFont = titleText->font();
    titleFont.setBold(true);
    titleFont.setPointSize(20);
    titleFont.setFamily("Ubuntu");

    titleText->setText("Register");
    titleText->setFont(titleFont);

    //setup signup Form
    userNameLabel->setText("UserName");
    userNameField->setPlaceholderText("Enter Your UserName");
    userNameBox->addWidget(userNameLabel, 1);
    userNameBox->addWidget(userNameField, 2);
    userNameBox->addStretch(4);

    emailLabel->setText("Email");
    emailField->setPlaceholderText("Enter Your Email");
    emailBox->addWidget(emailLabel, 1);
    emailBox->addWidget(emailField, 2);
    emailBox->addStretch(4);

    dobLabel->setText("Date of Birth");
    dobField->setPlaceholderText("DD-MM-YYYY");
    dateOfBirthBox->addWidget(dobLabel, 1);
    dateOfBirthBox->addWidget(dobField, 2);
    dateOfBirthBox->addStretch(4);

    passwordLabel->setText("Password");
    passwordField->setPlaceholderText("Enter Your Password");
    passwordField->setEchoMode(QLineEdit::Password);
    paswordBox->addWidget(passwordLabel, 1);
    paswordBox->addWidget(passwordField, 2);
    paswordBox->addStretch(4);

    comfirmPasswordLabel->setText("Confirm Password");
    comfirmPasswordField->setPlaceholderText("Confirm Your Password");
    comfirmPasswordField->setEchoMode(QLineEdit::Password);
    comfirmPasswordBox->addWidget(comfirmPasswordLabel, 1);
    comfirmPasswordBox->addWidget(comfirmPasswordField, 2);
    comfirmPasswordBox->addStretch(4);

    signupBtn->setText("Create Account");
    connect(signupBtn, &QPushButton::clicked, this, &Signup::on_create_account_btn_clicked);

    // Add all layouts to signup form container
    signUpFormContainer->addLayout(userNameBox, 1);
    signUpFormContainer->addLayout(emailBox, 1);
    signUpFormContainer->addLayout(dateOfBirthBox, 1);
    signUpFormContainer->addLayout(paswordBox, 1);
    signUpFormContainer->addLayout(comfirmPasswordBox, 1);
    signUpFormContainer->addWidget(signupBtn, 1);
    signUpFormContainer->addStretch(4);


    //setup signupContainer layout
    signUpContainer->addWidget(titleText, 1);
    signUpContainer->addLayout(signUpFormContainer, 5);
    signUpContainer->addWidget(divider, 1);
    signUpContainer->addWidget(socials, 1);

    // Set main container and centralise signup container
    mainContainer->addStretch(4);
    mainContainer->addLayout(signUpContainer, 2);
    mainContainer->addStretch(4);
    setLayout(mainContainer);

    // Set window properties
    setWindowTitle("Sign Up");
    setMinimumWidth(400);
    setMinimumHeight(600);
}

Signup::~Signup()
{
    // Clean up dynamically allocated memory
    delete mainContainer;
    delete signUpContainer;
    delete signUpFormContainer;
    delete titleText;
    delete userNameBox;
    delete userNameLabel;
    delete userNameField;
    delete emailBox;
    delete emailLabel;
    delete emailField;
    delete dateOfBirthBox;
    delete dobLabel;
    delete dobField;
    delete paswordBox;
    delete passwordLabel;
    delete passwordField;
    delete comfirmPasswordBox;
    delete comfirmPasswordLabel;
    delete comfirmPasswordField;
    delete signupBtn;
    delete divider;
    delete socials;
}

#include <regex>
#include <iostream>

bool Signup::validate_signup_form(QString& name, QString& email, QString& sex, QString& dob, QString& pass, QString& pass2, QString& errorMsg) {
    // Validate Username
    if(name.length() == 0 || email.length()==0 || sex.length()==0 || dob.length()==0 || pass.length()==0 || pass2.length()==0){
        errorMsg = "Fields cannot be left empty\n";
        return false;
    }
    if (name.length() < 3) {
        errorMsg = "User Name must be at least 3 characters\n";
        return false;
    }
    if (!name[0].isLetter()) {
        errorMsg = "User Name must start with a letter\n";
        return false;
    }

    // Validate Email
    if (!FormValidator::validateEmailAddress(email)) {
        errorMsg = "Invalid Email address\n";
        return false;
    }

    // Validate Date of Birth (dd/mm/yyyy)
    std::regex dob_pattern(R"((\d{2})\/(\d{2})\/(\d{4}))");
    if (std::regex_match(dob.toStdString(), dob_pattern)) {
        int day = std::stoi(dob.toStdString().substr(0, 2));
        int month = std::stoi(dob.toStdString().substr(3, 2));
        int year = std::stoi(dob.toStdString().substr(6, 4));
        if (day < 1 || day > 31 || month < 1 || month > 12) {
            errorMsg =  "Invalid date in Date of Birth\n";
            return false;
        }
    } else {
        errorMsg = "Date of Birth must be in dd/mm/yyyy format\n";
        return false;
    }

    // Validate Password
    if(!FormValidator::validatePassword(pass, errorMsg)){
        return false;
    }
    if (pass != pass2) {
        errorMsg = "Passwords do not match. Please confirm your password\n";
        return false;
    }

    return true;
}


void Signup::on_create_account_btn_clicked()
{
    // Get data from form
    QString name = userNameField->text();
    QString email = emailField->text();
    QString sex = "M";
    QString dob = dobField->text();
    QString pass = passwordField->text();
    QString pass2 = comfirmPasswordField->text();

    QString errorMsg;

    if(!validate_signup_form(name, email, sex, dob, pass, pass2, errorMsg)){
        QMessageBox::critical(this, errorMsg, errorMsg, QMessageBox::Ok);
        return;
    }

    // Create JSON payload
    QJsonObject jsonData;
    jsonData["user_name"] = name;
    jsonData["user_email"] = email;
    jsonData["user_sex"] = sex;
    jsonData["user_dob"] = dob;
    jsonData["user_bio"] = "";
    jsonData["password"] = HashHelper::hashString(pass);
    jsonData["created_at"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

    QJsonDocument jsonDoc(jsonData);
    QByteArray jsonDataBytes = jsonDoc.toJson();

    // Create and make Network Request
    ApiClient& apiClient = ApiClient::getInstance();
    QString url = ApiClient::getInstance().getUserDataUrl();
    QNetworkReply *reply = apiClient.makePostRequest(url, jsonData, "");

    // Connect to the finished signal to handle the response
    connect(reply, &QNetworkReply::finished, this, [=]() {
        qDebug() << "Received Reply";
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Received Has no error";
            // Request was successful
            QByteArray responseData = reply->readAll();
            QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
            QJsonObject responseJson = responseDoc.object();

            // Handle the server's response
            if (responseJson.contains("Status") && responseJson["Status"].toString() == "Created") {
                QMessageBox::information(this, "Account Created", "Account Created Successfully\nEnjoy Sharing Your Ideas", QMessageBox::Ok);
                emit signupSuccessful();
            } else {
                QString errorMessage = responseJson.contains("message") ? responseJson["message"].toString() : "Unknown error from server.";
                QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + errorMessage, QMessageBox::Ok);
            }
        } else {
            // Request failed
            QMessageBox::critical(this, "Signup Failed", "Creating Your Account Failed\n" + reply->errorString(), QMessageBox::Ok);
        }

        reply->deleteLater();
    });
}
