#include "socials.h"

SocialsWidget::SocialsWidget(QWidget *parent) {

    container = new QHBoxLayout();
    googleLogo = new QLabel(parent);
    facebookLogo = new QLabel(parent);

    googleLogo->setPixmap(QPixmap("../assets/google.png"));
    facebookLogo->setPixmap(QPixmap("../assets/facebook.png"));

    container->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    container->addWidget(googleLogo, 1);
    container->addWidget(facebookLogo, 1);
    container->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
}
