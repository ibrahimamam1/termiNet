#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QComboBox>
#include<vector>
#include"../widgets/clickablelabel.h"
#include "../widgets/createpost.h"
#include "../widgets/threadwidget.h"
#include "../../models/usermodel.h"
#include "../../models/communitymodel.h"
#include "../../db/communityrepository.h"
#include "../create_community/createcommunity.h"

class Home : public QMainWindow
{
    Q_OBJECT
    QVBoxLayout *mainContainer;
    QHBoxLayout *headerContainer;
    QHBoxLayout *bodyContainer;
    QVBoxLayout *leftArea;
    QVBoxLayout *threadsArea;
    QVBoxLayout *rightArea;
    QWidget *currentRightWidget;
    QVBoxLayout *centerArea; //can be threads or can be comments to a thread

    CreatePost* createPostWidget;
    //Messages* messageBoxWidget = nullptr;
    //Profile* profileWidget = nullptr;

    QLabel *logo;
    QLineEdit *searchBar; //is there a search bar widget in QT?
    ClickableLabel *createPostIcon;
    ClickableLabel *messageIcon;
    ClickableLabel *profileIcon;

    QVBoxLayout *homeNav;
    QLabel *homeNavHome;
    QLabel *homeNavPopular;
    QLabel *homeNavDiscover;

    QVBoxLayout *communityNav;
    QLabel* communityLabel;
    QLabel *createCommunity;

public:
    explicit Home(QWidget *parent = nullptr);
    void clearCenterWidget();
    void addThreadsToCenterWidget();
    void setUser(UserModel *usr);
    void showUserInfo();
    void loadThreads();
    void getUserCommunities(QVBoxLayout* layout);
    ~Home();

private slots:
    void onCreatePostIconClicked();
    void on_search_triggered();
    void on_message_icon_clicked();
    void on_profile_icon_clicked();
    void onCommentBtnClicked(int parentThreadId);
    void goBackToHomePressed();
    void onCreateCommunityBtnClicked();
    void onCommunityLabelClicked(CommunityModel community);

private:
    UserModel *user;
    std::vector<ThreadModel>threads;
    std::vector<ThreadModel>savedThreads;
    std::vector<CommunityModel>userCommunities;
};

#endif // HOME_H
