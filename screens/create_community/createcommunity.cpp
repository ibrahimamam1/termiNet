#include "createcommunity.h"
#include "../../db/communityrepository.h"
#include<QMessageBox>


CreateCommunity::CreateCommunity(QWidget *parent)
    :QWidget{parent}
{
    pageContainer = new QVBoxLayout(this);
    views = new QStackedWidget();
    page1 = new ComunityDescriptionPage();
    page2 = new CommunityBannerPage();
    page3 = new CategorySelectionScreen();
    bottombar = new QHBoxLayout();
    cancelBtn = new QPushButton("Cancel");
    prevBtn = new QPushButton("Previous");
    nextBtn = new QPushButton("Next");


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
        else if(currentIndex == views->count() - 1) {
            //do db operations
            QString comm_name = page1->communityNameField->text();
            QString comm_des = page1->communityDescription->toPlainText();
            QString comm_icon_path = page2->iconImagePath->text();
            QString comm_banner_path = page2->bannerImagePath->text();
            QImage iconImage(comm_icon_path);
            QImage bannerImage(comm_banner_path);
            std::vector<CategoryModel> categories_id = page3->getSelectedCategories();

            if(!CommunityRepository::addNewCommunity(CommunityModel(-1 ,comm_name, comm_des, iconImage, bannerImage, categories_id))){
                 QMessageBox *errorBox = new QMessageBox(QMessageBox::Critical, "Cannot Create Community", "Failed to create your community. Please Check your internet Connection and try again");
            }
            else{
                qDebug() << "Let's switch to community page";
            }

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

