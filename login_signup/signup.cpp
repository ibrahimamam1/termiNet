#include "signup.h"
#include "ui_signup.h"
#include "../db/user_repository.h"
#include<iostream>
#include<iomanip>
#include<string>
#include<cctype>

Signup::Signup(QWidget *parent, DatabaseManager* instance)
    : QDialog(parent)
    , ui(new Ui::Signup)
    , db(instance)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

#include <regex>
#include <iostream>

bool Signup::validate_signup_form(std::string name, std::string email, std::string sex, std::string dob, std::string pass, std::string pass2) {
    // Validate Username
    if(name.length() == 0 || email.length()==0 || sex.length()==0 || dob.length()==0 || pass.length()==0 || pass2.length()==0){
        qDebug() << "Fields cannot be left empty\n";
    }
    if (name.length() < 3) {
        qDebug() << "User Name must be at least 3 characters\n";
        return false;
    }
    if (!isalpha(name[0])) {
        qDebug() << "User Name cannot start with a number\n";
        return false;
    }

    // Validate Email
    std::regex email_pattern(R"((\w+)(\.{0,1})(\w*)@(\w+)\.(\w+))");
    if (!std::regex_match(email, email_pattern)) {
        qDebug() << "Invalid Email format\n";
        return false;
    }

    // Validate Date of Birth (dd/mm/yyyy)
    std::regex dob_pattern(R"((\d{2})\/(\d{2})\/(\d{4}))");
    if (std::regex_match(dob, dob_pattern)) {
        int day = std::stoi(dob.substr(0, 2));
        int month = std::stoi(dob.substr(3, 2));
        int year = std::stoi(dob.substr(6, 4));
        if (day < 1 || day > 31 || month < 1 || month > 12) {
            qDebug() << "Invalid date in Date of Birth\n";
            return false;
        }
    } else {
        qDebug() << "Date of Birth must be in dd/mm/yyyy format\n";
        return false;
    }

    // Validate Password
    bool is_char = false, is_number = false, is_alpha = false;
    if (pass.length() < 6) {
        qDebug() << "Password must be at least 6 characters long\n";
        return false;
    }
    for (char c : pass) {
        if (isalpha(c)) is_alpha = true;
        else if (isdigit(c)) is_number = true;
        else is_char = true;
        if (is_char && is_number && is_alpha) break;
    }
    if (!(is_char && is_number && is_alpha)) {
        qDebug() << "Password must contain at least one letter, one digit, and one special character\n";
        return false;
    }
    if (pass != pass2) {
        qDebug() << "Passwords do not match. Please confirm your password\n";
        return false;
    }

    return true;
}


void Signup::on_create_account_btn_clicked()
{
    //get data from form
    std::string name = ui->user_name->text().toStdString();
    std::string email = ui->user_email->text().toStdString();
    std::string sex = ui->user_sex->text().toStdString();
    std::string dob = ui->user_dob->text().toStdString();
    std::string pass = ui->user_pass->text().toStdString();
    std::string pass2 = ui->user_comfirm_pass->text().toStdString();
    time_t created_at = std::time(nullptr);

    if(validate_signup_form(name , email , sex , dob , pass, pass2)){

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
        UserRepository::addUserToDb(name, email, sex, dob_string, pass, created_at_string);
    }
    else
        qDebug() << "Invalid Form Data\n";


}


