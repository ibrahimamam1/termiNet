#ifndef APPHELPER_H
#define APPHELPER_H

class AppHelper
{
public:
    AppHelper();
    static void saveUserForPersistentLogin(const int& user_id);
    static const int checkPersitentLogin();
};

#endif // APPHELPER_H
