#ifndef APPHELPER_H
#define APPHELPER_H

#include <QString>
class AppHelper
{
public:
    AppHelper();
    static void saveUserForPersistentLogin(const int& user_id);
    static const int checkPersitentLogin();
    static const QString getDefaultProfilePicturePath();
};

#endif // APPHELPER_H
