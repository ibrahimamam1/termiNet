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
#include "../../models/communitymodel.h"

class CommunityPage : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    QScrollArea *scrollableArea;
    QVBoxLayout *communityInfoContainer;
    QWidget *threadContainer;
    QVBoxLayout *threadLayout;
    QLabel *communityName;
    QPushButton *joinBtn;
    QTextEdit *communityDescription;
    QLabel *bannerImage;
    QLabel *iconImage;
    QLabel *memberCount;
    CommunityModel community;

public:
    explicit CommunityPage(QWidget *parent = nullptr);
    void setCommunity(const CommunityModel& comm);

signals:

private slots:
    void onJoinBtnClicked();
};

#endif // COMMUNITYPAGE_H
