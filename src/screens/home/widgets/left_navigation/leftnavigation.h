#ifndef LEFTNAVIGATIONWIDGET_H
#define LEFTNAVIGATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include "../../../../models/community/communitymodel.h"
#include "../../../../models/user/usermodel.h"
#include "../../../../network/community/communityrepository.h"

class LeftNavigationWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QVBoxLayout *homeNav;
    QLabel *home;
    QLabel *popular;
    QLabel *discover;
    QScrollArea *communityScrollArea;
    QWidget *communityContent;

    QVBoxLayout *communityNav;
    QLabel* community;
    QLabel *createCommunity;

    QList<CommunityModel>userCommunities;
public:
    explicit LeftNavigationWidget(QWidget *parent = nullptr);
    void addUserCommunity(CommunityModel comm);
    void getUserCommunities(QVBoxLayout* layout);
    void onCreateCommunityBtnClicked();

signals:
    void homeClicked();

private slots:
    void onCommunityLabelClicked(CommunityModel community);
};

#endif // LEFTNAVIGATIONWIDGET_H
