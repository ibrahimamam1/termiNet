#ifndef COMMUNITYBANNERPAGE_H
#define COMMUNITYBANNERPAGE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

class CommunityBannerPage : public QWidget
{
    Q_OBJECT
public:
    explicit CommunityBannerPage(QWidget *parent = nullptr);
    QVBoxLayout *page2Layout;
    QHBoxLayout *bannerRow;
    QHBoxLayout *iconRow;

    QLabel *bannerText;
    QPushButton *bannerPickerBtn;
    QLabel *bannerImagePath;
    QLabel *iconText;
    QPushButton *iconPickerBtn;
    QLabel *iconImagePath;



signals:
};

#endif // COMMUNITYBANNERPAGE_H
