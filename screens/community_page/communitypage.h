#ifndef COMMUNITYPAGE_H
#define COMMUNITYPAGE_H

#include <QWidget>

#include "../widgets/topbar/customtopbar.h"
#include "../widgets/threadView/threadview.h"
#include "widgets/communitydescriptionwidget.h"

class CommunityPage : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    ThreadView *threadView;
    CommunityDescriptionWidget *communityDescriptionWidget;
    CommunityModel community;
    std::vector<ThreadModel> threads;

public:
    explicit CommunityPage(QWidget *parent = nullptr);
    CommunityModel getCommunity() const;
    void setCommunityPage(const CommunityModel& comm);
    void clearCommunityPage();

signals:

private slots:

};

#endif // COMMUNITYPAGE_H
