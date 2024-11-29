#include "createcommunity.h"

CreateCommunity::CreateCommunity(QWidget *parent)
    :QWidget{parent}
{
    pageContainer = new QVBoxLayout(this);
    views = new QStackedWidget();
    page1 = new QWidget();
    page2 = new QWidget();
    page3 = new QWidget();
    bottombar = new QHBoxLayout();
    cancelBtn = new QPushButton();
    prevBtn = new QPushButton();
    nextBtn = new QPushButton();

    //setup page1
    QVBoxLayout *page1Layout = new QVBoxLayout(page1);
    QLabel *headertext = new QLabel();
    headertext->setText("Create Your Own Amazing Communities");
    QLineEdit *communitNameField = new QLineEdit();
    communitNameField->setPlaceholderText("Community Name *");
    QTextEdit *communityDescription = new QTextEdit();
    communityDescription->setPlaceholderText("Description *");

    page1Layout->addWidget(headertext, 1);
    page1Layout->addWidget(communitNameField, 1);
    page1Layout->addWidget(communityDescription, 2);
    page1Layout->addStretch(1);

    //setup page2

    //setup page3

    //add pages to stackedWidget
    views->addWidget(page1);
    views->addWidget(page2);
    views->addWidget(page3);

    //setup bottom Bar
    bottombar->addWidget(cancelBtn, 1);
    bottombar->addStretch(3);
    bottombar->addWidget(prevBtn, 1);
    bottombar->addWidget(nextBtn, 1);

    //add everything to page container
    pageContainer->addWidget(views, 8);
    pageContainer->addLayout(bottombar, 2);

}

