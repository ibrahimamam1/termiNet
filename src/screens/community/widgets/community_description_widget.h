#ifndef COMMUNITYDESCRIPTIONWIDGET_H
#define COMMUNITYDESCRIPTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImageReader>
#include <QLabel>
#include <QTextEdit>
#include <QScrollArea>
#include <QPushButton>
#include "../../../models/community/communitymodel.h"

class CommunityDescriptionWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *communityInfoContainer;

    QLabel *communityName;
    QPushButton *joinBtn;
    QTextEdit *communityDescription;
    QLabel *bannerImage;
    QLabel *iconImage;
    QLabel *memberCount;
    CommunityModel community;
public:
    explicit CommunityDescriptionWidget(CommunityModel& community, QWidget *parent = nullptr);
    void setCommunity(const CommunityModel& comm);

signals:
    void communityJoined();

private slots:
    void onJoinBtnClicked();
};

#endif // COMMUNITYDESCRIPTIONWIDGET_H
