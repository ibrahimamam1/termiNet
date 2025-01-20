#include "banner_selection_widget.h"
#include "../../../../screens/styles/buttonStyles.h"

BannerSelectionWidget::BannerSelectionWidget(QWidget *parent)
    : QWidget{parent}
{
    page2Layout = new QVBoxLayout(this);
    bannerRow = new QHBoxLayout();
    iconRow = new QHBoxLayout();

    // Banner selection
    bannerText = new QLabel("Banner: ");
    bannerPickerBtn = new QPushButton("Select Banner");
    bannerPickerBtn->setStyleSheet(circularBtn);
    bannerPickerBtn->setIcon(QIcon("../../assets/imageIcon"));
    bannerImagePath = new QLabel();
    bannerRow->addWidget(bannerText);
    bannerRow->addWidget(bannerPickerBtn);
    bannerRow->addWidget(bannerImagePath);

    // Icon selection
    iconText = new QLabel("Icon: ");
    iconPickerBtn = new QPushButton("Select Icon");
    iconPickerBtn->setStyleSheet(circularBtn);
    iconPickerBtn->setIcon(QIcon("../../assets/imageIcon"));
    iconImagePath = new QLabel();
    iconRow->addWidget(iconText);
    iconRow->addWidget(iconPickerBtn);
    iconRow->addWidget(iconImagePath);

    // Connect banner picker button
    connect(bannerPickerBtn, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select Banner Image"), "", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
        if (!fileName.isEmpty()) {
            this->bannerImagePath->setText(fileName);
            qDebug() << "Selected Banner: " << fileName;
        }
    });

    // Connect icon picker button
    connect(iconPickerBtn, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Select Icon Image"), "", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
        if (!fileName.isEmpty()) {
            this->iconImagePath->setText(fileName);
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
}
