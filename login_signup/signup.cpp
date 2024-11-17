#include "signup.h"
#include "../db/user_repository.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<cctype>

Signup::Signup(QWidget *parent)
    : QDialog(parent)
    , db(DatabaseManager::getInstance())
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

bool Signup::validate_signup_form(std::string name, std::string email, std::string sex, std::string dob, std::string pass, std::string pass2, std::string& errorMsg) {
    // Validate Username
    if(name.length() == 0 || email.length()==0 || sex.length()==0 || dob.length()==0 || pass.length()==0 || pass2.length()==0){
        errorMsg = "Fields cannot be left empty\n";
        return false;
    }
    if (name.length() < 3) {
        errorMsg = "User Name must be at least 3 characters\n";
        return false;
    }
    if (!isalpha(name[0])) {
        errorMsg = "User Name cannot start with a number\n";
        return false;
    }

    // Validate Email
    std::regex email_pattern(R"((\w+)(\.{0,1})(\w*)@(\w+)\.(\w+))");
    if (!std::regex_match(email, email_pattern)) {
        errorMsg = "Invalid Email address\n";
        return false;
    }

    // Validate Date of Birth (dd/mm/yyyy)
    std::regex dob_pattern(R"((\d{2})\/(\d{2})\/(\d{4}))");
    if (std::regex_match(dob, dob_pattern)) {
        int day = std::stoi(dob.substr(0, 2));
        int month = std::stoi(dob.substr(3, 2));
        int year = std::stoi(dob.substr(6, 4));
        if (day < 1 || day > 31 || month < 1 || month > 12) {
            errorMsg =  "Invalid date in Date of Birth\n";
            return false;
        }
    } else {
        errorMsg = "Date of Birth must be in dd/mm/yyyy format\n";
        return false;
    }

    // Validate Password
    bool is_char = false, is_number = false, is_alpha = false;
    if (pass.length() < 6) {
        errorMsg = "Password must be at least 6 characters long\n";
        return false;
    }
    for (char c : pass) {
        if (isalpha(c)) is_alpha = true;
        else if (isdigit(c)) is_number = true;
        else is_char = true;
        if (is_char && is_number && is_alpha) break;
    }
    if (!(is_char && is_number && is_alpha)) {
        errorMsg = "Password must contain at least one letter, one digit, and one special character\n";
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
    //get data from form
    std::string name = userNameField->text().toStdString();
    std::string email = emailField->text().toStdString();
    std::string sex = "M";
    std::string dob = dobField->text().toStdString();
    std::string pass = passwordField->text().toStdString();
    std::string pass2 = comfirmPasswordField->text().toStdString();
    time_t created_at = std::time(nullptr);

    std::string errorMsg;

    if(!validate_signup_form(name , email , sex , dob , pass, pass2, errorMsg)){
        //show appropriate error Message
        QMessageBox errorBox;
        errorBox.setIcon(QMessageBox::Critical);
        errorBox.setWindowTitle("Invalid Data Failed");
        errorBox.setText(QString::fromStdString(errorMsg));
        errorBox.setInformativeText("Please Try Again");
        errorBox.exec();
    }
    else
    {

        // convert dob and created_at to a postgres compatible type
        std::tm tm = {};
        std::istringstream ss(dob);

        // Parse the date in "dd/mm/yyyy" format
        ss >> std::get_time(&tm, "%d/%m/%Y");


        // Convert std::tm to time_t
        time_t date_of_birth =  std::mktime(&tm);

        //convert dob to postgre compatible type
        std::tm *ptm = std::localtime(&date_of_birth);
        char dob_string[11];
        strftime(dob_string, sizeof(dob_string), "%Y-%m-%d", ptm);

        //convert created_at to postgre compatible type
        ptm = std::localtime(&created_at);
        char created_at_string[11];
        strftime(created_at_string, sizeof(created_at_string), "%Y-%m-%d", ptm);

        //add user entry to DB, static void addUserToDb(std::string name, std::string email, std::string sex, char* dob, char* created_at);
       bool addedUser = UserRepository::addUserToDb(name, email, sex, dob_string, pass, created_at_string);
        if(addedUser){
            //show success message
            QMessageBox errorBox;
            errorBox.setIcon(QMessageBox::Information);
            errorBox.setWindowTitle("Account Created");
            errorBox.setText("Account Created Successfully");
            errorBox.setInformativeText("Enjoy Sharing Your Ideas");

           emit signupSuccessful();

        }else{
            //show error message and retry
            QMessageBox errorBox;
            errorBox.setIcon(QMessageBox::Critical);
            errorBox.setWindowTitle("Signup Failed");
            errorBox.setText("Creating Your Account Failed");
            errorBox.setInformativeText("Please Check Your Internet Connection");
            errorBox.exec();
        }
    }


}

