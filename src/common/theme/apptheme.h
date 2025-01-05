#ifndef APPTHEME_H
#define APPTHEME_H

#include <QObject>

class AppTheme : public QObject
{
    Q_OBJECT
public:
    explicit AppTheme(QObject *parent = nullptr);

    static QPalette getDarkPalette();
    static QPalette getLightPalette();

signals:
};

#endif // APPTHEME_H
