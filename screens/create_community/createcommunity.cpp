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
    cancelBtn = new QPushButton("Cancel");
    prevBtn = new QPushButton("Previous");
    nextBtn = new QPushButton("Next");

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
    QVBoxLayout *page2Layout = new QVBoxLayout(page2);
    QHBoxLayout *bannerRow = new QHBoxLayout();
    QHBoxLayout *iconRow = new QHBoxLayout();

    // Banner selection
    QLabel *bannerText = new QLabel("Banner: ");
    QPushButton *bannerPickerBtn = new QPushButton("Select Banner");
    bannerRow->addWidget(bannerText);
    bannerRow->addWidget(bannerPickerBtn);

    // Icon selection
    QLabel *iconText = new QLabel("Icon: ");
    QPushButton *iconPickerBtn = new QPushButton("Select Icon");
    iconRow->addWidget(iconText);
    iconRow->addWidget(iconPickerBtn);

    // Connect banner picker button
    connect(bannerPickerBtn, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select Banner Image"), "", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
        if (!fileName.isEmpty()) {
            // TODO: Handle the selected banner image (e.g., display preview, store path)
            qDebug() << "Selected Banner: " << fileName;
        }
    });

    // Connect icon picker button
    connect(iconPickerBtn, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select Icon Image"), "", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));

        if (!fileName.isEmpty()) {
            // TODO: Handle the selected icon image (e.g., display preview, store path)
            qDebug() << "Selected Icon: " << fileName;
        }
    });

    bannerRow->addWidget(bannerText);
    bannerRow->addWidget(bannerPickerBtn);
    iconRow->addWidget(iconText);
    iconRow->addWidget(iconPickerBtn);

    page2Layout->addLayout(bannerRow, 1);
    page2Layout->addLayout(iconRow, 2);
    page2Layout->addStretch(2);

    //setup page3
    QVBoxLayout *page3Layout = new QVBoxLayout(page3);
    QLabel *topicText = new QLabel("Select Topics");

    page3Layout->addWidget(topicText);

    //add pages to stackedWidget
    views->addWidget(page1);
    views->addWidget(page2);
    views->addWidget(page3);

    //configure navigation between pages
    connect(nextBtn, &QPushButton::clicked, [=]() {
        int currentIndex = views->currentIndex();
        if (currentIndex < views->count() - 1) {
            views->setCurrentIndex(currentIndex + 1);
        }
    });
    connect(prevBtn,&QPushButton::clicked, [=]() {
        int currentIndex = views->currentIndex();
        if (currentIndex > 0) {
            views->setCurrentIndex(currentIndex - 1);
        }
    });
    connect(cancelBtn,&QPushButton::clicked, [=]() {
        qDebug() << "Will go back to Home";
    });

    //setup bottom Bar
    bottombar->addWidget(cancelBtn, 1);
    bottombar->addStretch(3);
    bottombar->addWidget(prevBtn, 1);
    bottombar->addWidget(nextBtn, 1);

    //add everything to page container
    pageContainer->addWidget(views, 8);
    pageContainer->addLayout(bottombar, 2);

}

