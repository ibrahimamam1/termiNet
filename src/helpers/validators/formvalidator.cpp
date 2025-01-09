#include "formvalidator.h"
#include <regex>

FormValidator::FormValidator() {}

bool FormValidator::validateUserName(const QString& name, QString& error_msg){
    if (name.length() < 3) {
        error_msg = "User Name must be at least 3 characters\n";
        return false;
    }
    if (!name[0].isLetter()) {
        error_msg = "User Name must start with a letter\n";
        return false;
    }
    return true;
}

bool FormValidator::validateEmailAddress(const QString &email){

    std::regex email_pattern(R"((\w+)(\.{0,1})(\w*)@(\w+)\.(\w+))");
    if (!std::regex_match(email.toStdString(), email_pattern))
        return false;

    return true;
}

bool FormValidator::validatePassword(const QString& pass, QString& errorMsg){

    bool is_char = false, is_number = false, is_alpha = false;
    if (pass.length() < 6) {
        errorMsg = "Password must be at least 6 characters long\n";
        return false;
    }
    for (auto c : pass) {
        if (c.isLetter()) is_alpha = true;
        else if (c.isDigit()) is_number = true;
        else is_char = true;
        if (is_char && is_number && is_alpha) break;
    }
    if (!(is_char && is_number && is_alpha)) {
        errorMsg = "Password must contain at least one letter, one digit, and one special character\n";
        return false;
    }
    return true;
}

