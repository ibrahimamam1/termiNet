#ifndef COMMUNITYPAGE_H
#define COMMUNITYPAGE_H

#include <QWidget>

#include "../home/widgets/topBar/topbar.h"
#include "../home/widgets/thread_view/threadview.h"
#include "widgets/community_description_widget.h"

class CommunityPage : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    ThreadView *threadView;
    CommunityDescriptionWidget *communityDescriptionWidget;
    CommunityModel community;
    QList<ThreadModel> threads;
    bool isSet = false;
    bool joined = false;

public:
    explicit CommunityPage(QWidget *parent = nullptr);
    CommunityModel getCommunity() const;
    void setCommunityPage(const CommunityModel& comm);

signals:

private slots:

};

#endif // COMMUNITYPAGE_H
