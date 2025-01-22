#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>
#include "../../models/community/communitymodel.h"
#include "../../models/thread/threadmodel.h"
#include "../../models/user/usermodel.h"

class SearchView : public QWidget
{
    Q_OBJECT

    QTabWidget *tabs;

    QList<ThreadModel> threads;
    QList<CommunityModel> communities;
    QList<UserModel> users;

    void updateThreadsTab(const QList<ThreadModel>& threads);
    void updateCommunitiesTab(const QList<CommunityModel>& communities);
    void updateUsersTab(const QList<UserModel>& users);

public:
    explicit SearchView(QWidget *parent = nullptr);
    void setSearchView(const QList<ThreadModel>& threads, const QList<CommunityModel>& comms, const QList<UserModel>& users);

signals:
         // You can add signals here if needed
};

#endif // SEARCHVIEW_H
