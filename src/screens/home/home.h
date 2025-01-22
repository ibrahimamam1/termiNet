#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include<vector>
#include "widgets/topBar/topbar.h"
#include "widgets/left_navigation/leftnavigation.h"
#include"../../common/widgets//clickable_label.h"
#include "widgets/thread_view/widgets/thread/threadwidget.h"
#include "../../models/user/usermodel.h"
#include "../../models/community/communitymodel.h"
#include "../../network/community/communityrepository.h"
#include "../../screens/create_community/createcommunity.h"
#include "../community/communitypage.h"
#include "widgets/thread_view/threadview.h"
#include "../../models/user/authenticateduser.h"
#include "../message/messagepage.h"
#include "../../screens/profile/profileview.h"
#include "../../screens/search/searchview.h"

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    void addThreadsToCenterWidget();
    void setUser(UserModel *usr);
    void showUserInfo();
    void loadThreads();

    static Home& getInstance();
    ~Home();

    QVBoxLayout *mainContainer;
    QHBoxLayout *bodyContainer;
    CustomTopBar *topBar;
    LeftNavigationWidget *leftNav;
    QStackedWidget *centerArea;
    ThreadView *threadView;
    ProfileView *profileview;
    SearchView *searchView;
    CommunityPage *communityPage;
    MessagePage *msgPage;
    bool profileVisible;

private slots:

    void onCommentBtnClicked(const ThreadModel& parentThread);
    void onMessageIconClicked();
    void onProfileIconClicked();
    void onPostCreated(bool success);
    void onSearchActivated(const QString& searchString);

private:
    UserModel& user;
    static std::unique_ptr<Home> instance;
    QList<ThreadModel>threads;
    QList<ThreadModel>savedThreads;
};

#endif // HOME_H
