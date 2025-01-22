#include "createcommunity.h"
#include "../../network/community/communityrepository.h"
#include "../../../helpers/apphelper.h"
#include "../home/home.h"
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
            //Scale the icon and banner images
            QImage scaledIconImage = AppHelper::createRoundedIcon(iconImage);
            QImage scaledBannerImage = bannerImage.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QList<CategoryModel> categories_id = page3->getSelectedCategories();

            CommunityModel community(comm_name, comm_des, scaledIconImage, scaledBannerImage);
            community.setCategories(categories_id);
            if(!CommunityRepository::addNewCommunity(community)){
                QMessageBox *errorBox = new QMessageBox(QMessageBox::Critical, "Cannot Create Community", "Failed to create your community. Please Check your internet Connection and try again");
            }
            else{
                QMessageBox::information(this, "Sucess", "Your Community Have been Created Succesfully", "Ok");

                Home& home = Home::getInstance();
                community.setJoined(true);
                home.leftNav->addUserCommunity(community);
                home.communityPage->setCommunityPage(community);
                this->hide();
                home.centerArea->setCurrentIndex(1);
            }

        }
    });
    connect(prevBtn,&QPushButton::clicked, [=]() {
        int currentIndex = pages->currentIndex();
        if (currentIndex > 0) {
            pages->setCurrentIndex(currentIndex - 1);
        }
    });
    connect(cancelBtn,&QPushButton::clicked, [&]() {
        this->hide();
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

