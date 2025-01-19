#ifndef COMMUNITYPAGE_H
#define COMMUNITYPAGE_H

#include <QWidget>

#include "../../src/screens/home/widgets/topBar/topbar.h"
#include "../../src/screens/home/widgets/thread_view/threadview.h"
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
