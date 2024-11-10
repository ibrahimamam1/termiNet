#include "signup.h"
#include "ui_signup.h"
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
    qDebug() << "Retreiving Data From Form";

    std::string name = ui->user_name->text().toStdString();
    std::string email = ui->user_email->text().toStdString();
    std::string sex = ui->user_sex->text().toStdString();
    std::string dob = ui->user_dob->text().toStdString();
    std::string pass = ui->user_pass->text().toStdString();
    std::string pass2 = ui->user_comfirm_pass->text().toStdString();
    time_t created_at = std::time(nullptr);

    if(validate_signup_form(name , email , sex , dob , pass, pass2)){
        qDebug() << "Valid Form Data\n";

        // convert dob from std string and created_at from a time_t  to a postgres compatible type

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

        qDebug() << created_at_string;


        //add user entry to DB , will trigger a trigger which handles id generation , auth and hash generation on server side

        // QSqlQuery q;
        // q.prepare(
        //     "INSERT into users(user_id, user_name, user_email, user_sex, user_dob, user_bio, created_at)"
        //     "values(:user_id, :user_name, :user_email, :user_sex, :user_dob,:user_bio, :created_at)"
        //     );

        // q.bindValue(":user_id", 0);
        // q.bindValue(":user_name",  QString::fromStdString(name));
        // q.bindValue(":user_email", QString::fromStdString(email));
        // q.bindValue(":user_sex",   QString::fromStdString(sex));
        // q.bindValue(":user_dob",   QString::fromStdString(dob_string));
        // q.bindValue(":user_bio",   QString::fromStdString(" "));
        // q.bindValue(":created_at", QString::fromStdString(created_at_string));

        // if (!q.exec()) {
        //     qDebug() << "Insert failed:" << q.lastError().text();
        // } else {
        //     qDebug() << "Insert successful";
        // }

        QSqlQuery q;
        q.exec();
    }
    else
        qDebug() << "Invalid Form Data\n";

    // //make a new User Model
    // db->create_auth_entry(user);

    // //if create auth is succesfull
    // db->add_new_user(user);
}
void Signup::readUserTable() {
    QSqlQuery query;

    // Execute the SELECT query
    if (query.exec("SELECT user_id, user_name, user_email, user_sex, user_dob, created_at FROM users")) {
        // Iterate over each row in the result set
        while (query.next()) {
            int userId = query.value("user_id").toInt();
            QString userName = query.value("user_name").toString();
            QString userEmail = query.value("user_email").toString();
            QString userSex = query.value("user_sex").toString();
            QString userDob = query.value("user_dob").toString();
            QString createdAt = query.value("created_at").toString();

            // Print the user details
            qDebug() << "User ID:" << userId
                     << "Name:" << userName
                     << "Email:" << userEmail
                     << "Sex:" << userSex
                     << "DOB:" << userDob
                     << "Created At:" << createdAt;
        }
    } else {
        // Print error if the query execution fails
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
}

