#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../../../src/common/widgets/clickable_label.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QIcon>
class ProfileView : public QWidget
{
    Q_OBJECT
    QVBoxLayout mainLayout;
    QLabel *profilePic;
    QIcon profileIcon;
    ClickableLabel *changeProfilePic;
    QLineEdit *userName;
    QPushButton *changeUserName;
    QLineEdit *userEmail;
    QPushButton *changeUserEmail;
    QDateEdit *userDob;
    QPushButton *changeUserDob;
    QLineEdit *userBio;
    QPushButton *changeUserBio;
    QPushButton *save;

public:
    explicit ProfileView(QWidget *parent = nullptr);

signals:

private slots:
    void onSaveButtonClicked();
};

#endif // PROFILEVIEW_H
