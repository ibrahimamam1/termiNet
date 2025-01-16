#ifndef APPHELPER_H
#define APPHELPER_H

#include <QString>
#include <QJsonDocument>
class AppHelper
{
public:
    AppHelper();
    static void saveUserForPersistentLogin(const QString& user_id);
    static const QString checkPersitentLogin();
    static const QString getDefaultProfilePicturePath();
    static const QJsonDocument loadJsonFromFile(const QString& filePath);
};

#endif // APPHELPER_H
