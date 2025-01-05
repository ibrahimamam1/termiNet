#ifndef FORMVALIDATOR_H
#define FORMVALIDATOR_H
#include <QString>
class FormValidator
{
public:
    FormValidator();
    static bool validateEmailAddress(const QString& email);
    static bool validatePassword(const QString& pass, QString& errorMsg);
};

#endif // FORMVALIDATOR_H
