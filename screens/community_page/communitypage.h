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
#include "../widgets/topbar/customtopbar.h"

class CommunityPage : public QWidget
{
    Q_OBJECT
    QVBoxLayout *communityPageLayout;
    QHBoxLayout *bodyLayout;
    QScrollArea *scrollableArea;
    QWidget *threadContainer;
    QVBoxLayout *threadLayout;
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
