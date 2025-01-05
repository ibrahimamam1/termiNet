#include "socials.h"

SocialsWidget::SocialsWidget(QWidget *parent) {

    container = new QHBoxLayout(this);
    googleLogo = new QLabel();
    facebookLogo = new QLabel();

    googleLogo->setPixmap(QPixmap("../../assets/google.png"));
    facebookLogo->setPixmap(QPixmap("../../assets/facebook.png"));

    container->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    container->addWidget(googleLogo, 1);
    container->addWidget(facebookLogo, 1);
    container->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
}
