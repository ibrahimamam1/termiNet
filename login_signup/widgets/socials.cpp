#include "socials.h"
#include "../../src/network/login/loginrepository.h"

SocialsWidget::SocialsWidget(QWidget *parent) {

    container = new QHBoxLayout(this);
    googleLogo = new ClickableLabel();
    facebookLogo = new ClickableLabel();

    googleLogo->setPixmap(QPixmap("../../assets/google.png"));
    QObject::connect(googleLogo, &ClickableLabel::clicked, this, [=]{
        emit googleLoginClicked();
    });
    facebookLogo->setPixmap(QPixmap("../../assets/facebook.png"));
    QObject::connect(facebookLogo, &ClickableLabel::clicked, this, [=]{
        emit facebookLoginClicked();
    });

    container->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    container->addWidget(googleLogo, 1);
    container->addWidget(facebookLogo, 1);
    container->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
}

