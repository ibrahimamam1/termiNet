#ifndef CUSTOMTOPBAR_H
#define CUSTOMTOPBAR_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "../../../../common/widgets/clickable_label.h"
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
    void onPostCreated(bool success);

signals:
    void messageIconClicked();
    void profileIconClicked();
    void postCreated(bool success);
    void searchActivated(const QString target);
};

#endif // CUSTOMTOPBAR_H
