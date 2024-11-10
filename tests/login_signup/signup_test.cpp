#include <cassert>
#include <QApplication>
#include "../../login_signup/signup.h"
#include "../../db/databasemanager.h"

void test_validate_signup_form() {
    DatabaseManager* db;
    Signup signup(nullptr , db);

    // Username edge cases
    assert(!signup.validate_signup_form("Jo", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Username too short - should fail");
    assert(!signup.validate_signup_form("1John", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Username starts with a digit - should fail");
    assert(!signup.validate_signup_form("John!", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Username contains special character - should fail");
    assert(signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Valid username - should pass");

    // Email edge cases
    assert(!signup.validate_signup_form("John", "invalid-email", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Invalid email format (no @, domain) - should fail");
    assert(!signup.validate_signup_form("John", "test@.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Invalid email format (no domain name) - should fail");
    assert(signup.validate_signup_form("John", "user.name@domain.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Valid email format - should pass");

    // Date of Birth edge cases
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "32/01/2000", "Pass123!", "Pass123!") &&
           "Invalid day in date - should fail");
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "01/13/2000", "Pass123!", "Pass123!") &&
           "Invalid month in date - should fail");
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "01/01/20", "Pass123!", "Pass123!") &&
           "Invalid year format in date - should fail");
    assert(signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Valid date format - should pass");

    // Password edge cases
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "12345", "12345") &&
           "Password too short - should fail");
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "password", "password") &&
           "Password missing digit and special character - should fail");
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "pass123", "pass123") &&
           "Password missing special character - should fail");
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass321!") &&
           "Passwords do not match - should fail");
    assert(signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Valid password with matching confirm - should pass");

    // Additional edge cases
    assert(!signup.validate_signup_form("", "test@example.com", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Empty username - should fail");
    assert(!signup.validate_signup_form("John", "", "M", "01/01/2000", "Pass123!", "Pass123!") &&
           "Empty email - should fail");
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "", "Pass123!", "Pass123!") &&
           "Empty date of birth - should fail");
    assert(!signup.validate_signup_form("John", "test@example.com", "M", "01/01/2000", "", "Pass123!") &&
           "Empty password - should fail");

    qDebug() << "All tests passed!";
}
