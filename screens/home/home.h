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
#include "../widgets/thread//threadwidget.h"
#include "../../src/models/user/usermodel.h"
#include "../../models/community/communitymodel.h"
#include "../../db/communityrepository.h"
#include "../create_community/createcommunity.h"
#include "../community_page/communitypage.h"
#include "../widgets/threadView/threadview.h"
#include "../../src/models/user/authenticateduser.h"
#include "../message/messagepage.h"
#include "../profile_view/profileview.h"

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
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
    ThreadView *threadView;
    ProfileView *profileview;
    CommunityPage *communityPage;
    MessagePage *msgPage;
    bool profileVisible;

private slots:

    void onCommentBtnClicked(int parentThreadId);
    void onMessageIconClicked();
    void onProfileIconClicked();

private:
    UserModel *user;
    static Home *instance;
    std::vector<ThreadModel>threads;
    std::vector<ThreadModel>savedThreads;
};

#endif // HOME_H
