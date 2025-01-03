#ifndef CUSTOMTOPBAR_H
#define CUSTOMTOPBAR_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "../clickablelabel.h"
#include "../createPost//createpost.h"

class CustomTopBar : public QWidget
{
    Q_OBJECT
    QHBoxLayout *headerContainer;
    QLabel *logo;
    QLineEdit *searchBar; //is there a search bar widget in QT?
    ClickableLabel *createPostIcon;
    ClickableLabel *messageIcon;
    ClickableLabel *profileIcon;
public:
    explicit CustomTopBar(QWidget *parent = nullptr);

private slots:
    void onCreatePostIconClicked();
    void onSearchTriggered();
    void onMessageIconClicked();
    void onProfileIconClicked();

signals:
    void messageIconClicked();
    void profileIconClicked();
};

#endif // CUSTOMTOPBAR_H
