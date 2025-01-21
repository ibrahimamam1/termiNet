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
public:
    explicit CommunityDescriptionWidget(CommunityModel& community, QWidget *parent = nullptr);

signals:

private slots:
    void onJoinBtnClicked();
};

#endif // COMMUNITYDESCRIPTIONWIDGET_H
