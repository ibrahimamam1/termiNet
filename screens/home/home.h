#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include<vector>
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
    QLabel *createPostIcon;
    QLabel *messageIcon;
    QLabel *profileIcon;

    QVBoxLayout *homeNav;
    QLabel *homeNavHome;
    QLabel *homeNavPopular;
    QLabel *homeNavDiscover;

    QVBoxLayout *communityNav;
    QLabel* communityLabel;

public:
    explicit Home(QWidget *parent = nullptr);
    void clearCenterWidget();
    void setUser(UserModel *usr);
    void showUserInfo();
    void loadThreads();
    void showThreads();
    ~Home();

private slots:
    void on_create_post_icon_clicked();
    void on_search_triggered();
    void on_message_icon_clicked();
    void on_profile_icon_clicked();

private:
    UserModel *user;
    std::vector<ThreadModel>threads;
};

#endif // HOME_H
