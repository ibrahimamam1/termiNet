#include "createcommunity.h"
#include "../../../db/communityrepository.h"
#include<QMessageBox>


CreateCommunity::CreateCommunity(QWidget *parent)
    :QWidget{parent}
{
    pageContainer = new QVBoxLayout(this);
    pages = new QStackedWidget();
    page1 = new ComunityDescriptionWidget();
    page2 = new BannerSelectionWidget();
    page3 = new CategorySelectionWidget();
    bottombar = new QHBoxLayout();
    cancelBtn = new QPushButton("Cancel");
    prevBtn = new QPushButton("Previous");
    nextBtn = new QPushButton("Next");


    //add pages to stackedWidget
    pages->addWidget(page1);
    pages->addWidget(page2);
    pages->addWidget(page3);

    //configure navigation between pages
    connect(nextBtn, &QPushButton::clicked, [=]() {
        int currentIndex = pages->currentIndex();
        if (currentIndex == 0) {
            QString name = page1->communityNameField->text();
            QString des = page1->communityDescription->toPlainText();
            if(name.isEmpty() || des.isEmpty()){
                QMessageBox::critical(this, "Input Error", "Please Fill all fields", QMessageBox::Ok);
            }else{
                pages->setCurrentIndex(1);
            }
        }else if(currentIndex < pages->count() - 1){
            pages->setCurrentIndex(pages->currentIndex() + 1);
        }
        else if(currentIndex == pages->count() - 1) {
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
        int currentIndex = pages->currentIndex();
        if (currentIndex > 0) {
            pages->setCurrentIndex(currentIndex - 1);
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
    pageContainer->addWidget(pages, 8);
    pageContainer->addLayout(bottombar, 2);

}

