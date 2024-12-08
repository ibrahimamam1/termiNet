#ifndef COMMUNITYPAGE_H
#define COMMUNITYPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImageReader>
#include <QLabel>
#include <QTextEdit>
#include <QScrollArea>
#include <QPushButton>

class CommunityPage : public QWidget
{
    Q_OBJECT
    QScrollArea *mainContainer;
    QVBoxLayout *threadContainer;
    QLabel *communityName;
    QLabel *communityIcon;
    QPushButton *joinBtn;
    QTextEdit *communityDescription;
    QLabel *bannerImage;


public:
    explicit CommunityPage(QWidget *parent = nullptr);

signals:
};

#endif // COMMUNITYPAGE_H
