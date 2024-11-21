#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include<vector>
#include"../widgets/clickablelabel.h"
#include "../widgets/createpost.h"
#include "../widgets/threadwidget.h"
#include "../../models/usermodel.h"

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

public:
    explicit Home(QWidget *parent = nullptr);
    void clearCenterWidget();
    void addThreadsToCenterWidget();
    void setUser(UserModel *usr);
    void showUserInfo();
    void loadThreads();
    void showThreads();
    ~Home();

private slots:
    void onCreatePostIconClicked();
    void on_search_triggered();
    void on_message_icon_clicked();
    void on_profile_icon_clicked();
    void onCommentBtnClicked(int parentThreadId);
    void goBackToHomePressed();

private:
    UserModel *user;
    std::vector<ThreadModel>threads;
    std::vector<ThreadModel>savedThreads;
};

#endif // HOME_H
