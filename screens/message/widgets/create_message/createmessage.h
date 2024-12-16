#ifndef CREATEMESSAGE_H
#define CREATEMESSAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QSqlQuery>
#include "../../../../models/user/usermodel.h"

class CreateMessage : public QWidget
{
    Q_OBJECT
    QLineEdit *searchBar;
    QLabel *userStatusLabel;
    QVBoxLayout *mainLayout;

public:
    explicit CreateMessage(QWidget *parent = nullptr);

signals:
    void userSelected(UserModel receiver);

private slots:
    void onSearchReturnPressed();
    void onUserLinkClicked();

private:
    void searchUser();
    UserModel  receiver;
};

#endif // CREATEMESSAGE_H
