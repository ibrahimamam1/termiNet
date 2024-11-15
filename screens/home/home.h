#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include "../widgets/createpost.h"
#include "../../models/usermodel.h"

namespace Ui {
    class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT
    QWidget* currentRightWidget = nullptr;

    CreatePost* createPostWidget = nullptr;
    //Messages* messageBoxWidget = nullptr;
    //Profile* profileWidget = nullptr;

public:
    explicit Home(QWidget *parent = nullptr);
    void setUser(UserModel *usr);
    void showUserInfo();
    ~Home();

private slots:
    void on_create_post_btn_clicked();

private:
    Ui::Home *ui;
    UserModel *user;
};

#endif // HOME_H
