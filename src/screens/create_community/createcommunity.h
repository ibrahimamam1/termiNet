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

#include "widgets/category_selection/category_selection_widget.h"
#include "widgets/community_description/community_description_widget.h"
#include "widgets/banner_selection/banner_selection_widget.h"

class CreateCommunity : public QWidget
{
    Q_OBJECT
    QVBoxLayout *pageContainer;
    QStackedWidget *pages;
    ComunityDescriptionWidget *page1;
    BannerSelectionWidget *page2;
    CategorySelectionWidget *page3;
    QHBoxLayout *bottombar;
    QPushButton *cancelBtn;
    QPushButton *prevBtn;
    QPushButton *nextBtn;

public:
    explicit CreateCommunity(QWidget *parent = nullptr);

signals:
};

#endif // CREATECOMMUNITY_H
