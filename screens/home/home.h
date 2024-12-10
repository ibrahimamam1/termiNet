#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include<vector>
#include "../widgets/topbar/customtopbar.h"
#include "../widgets/leftNavigation/leftnavigationwidget.h"
#include"../widgets/clickablelabel.h"
#include "../widgets/createpost.h"
#include "../widgets/threadwidget.h"
#include "../../models/usermodel.h"
#include "../../models/communitymodel.h"
#include "../../db/communityrepository.h"
#include "../create_community/createcommunity.h"
#include "../community_page/communitypage.h"

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    void clearCenterWidget();
    void addThreadsToCenterWidget();
    void setUser(UserModel *usr);
    void showUserInfo();
    void loadThreads();

    static Home* getInstance();
    ~Home();

    QVBoxLayout *mainContainer;
    QHBoxLayout *bodyContainer;
    CustomTopBar *topBar;
    LeftNavigationWidget *leftNav;
    QStackedWidget *centerArea;
    QWidget *homeThreads;
    QVBoxLayout *homeThreadsLayout;
    CommunityPage *communityPage;
    QVBoxLayout *rightArea;
    QWidget *currentRightWidget;

private slots:

    void onCommentBtnClicked(int parentThreadId);

private:
    UserModel *user;
    static Home *instance;
    std::vector<ThreadModel>threads;
    std::vector<ThreadModel>savedThreads;
};

#endif // HOME_H
