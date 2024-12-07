#ifndef CREATECOMMUNITY_H
#define CREATECOMMUNITY_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

#include "pages/categoryselectionscreen.h"
#include "pages/comunitydescriptionpage.h"
#include "pages/communitybannerpage.h"

class CreateCommunity : public QWidget
{
    Q_OBJECT
    QVBoxLayout *pageContainer;
    QStackedWidget *views;
    ComunityDescriptionPage *page1;
    CommunityBannerPage *page2;
    CategorySelectionScreen *page3;
    QHBoxLayout *bottombar;
    QPushButton *cancelBtn;
    QPushButton *prevBtn;
    QPushButton *nextBtn;

public:
    explicit CreateCommunity(QWidget *parent = nullptr);

signals:
};

#endif // CREATECOMMUNITY_H
