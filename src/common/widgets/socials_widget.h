#ifndef SOCIALS_H
#define SOCIALS_H
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
#include "clickable_label.h"

class SocialsWidget: public QWidget
{
    Q_OBJECT

    QHBoxLayout *container;
    ClickableLabel* googleLogo;
    ClickableLabel* facebookLogo;

public:
    SocialsWidget(QWidget *parent = nullptr){
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
signals:
    void googleLoginClicked();
    void facebookLoginClicked();
};

#endif // SOCIALS_H
