#ifndef SOCIALS_H
#define SOCIALS_H
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
#include "../../src/common/widgets/clickable_label.h"

class SocialsWidget: public QWidget
{
    QHBoxLayout *container;
    ClickableLabel* googleLogo;
    ClickableLabel* facebookLogo;

public:
    SocialsWidget(QWidget *parent = nullptr);

private slots:
    void onGoogleLoginClicked();
};

#endif // SOCIALS_H
