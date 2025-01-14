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

    container->addStretch();
    container->addWidget(googleLogo);
    container->addSpacing(20);
    container->addWidget(facebookLogo);
    container->addStretch();

    this->setLayout(container);
}

