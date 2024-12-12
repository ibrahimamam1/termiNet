#ifndef APPHELPER_H
#define APPHELPER_H
#include <QImage>
class AppHelper
{
public:
    AppHelper();
    static QImage createRoundedIcon(const QImage& sourceImage, int diameter);
};

#endif // APPHELPER_H
