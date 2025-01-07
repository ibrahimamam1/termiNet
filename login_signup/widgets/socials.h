#ifndef SOCIALS_H
#define SOCIALS_H
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
#include "../../src/common/widgets/clickable_label.h"

class SocialsWidget: public QWidget
{
    Q_OBJECT

    QHBoxLayout *container;
    ClickableLabel* googleLogo;
    ClickableLabel* facebookLogo;

public:
    SocialsWidget(QWidget *parent = nullptr);
signals:
    void googleLoginClicked();
    void facebookLoginClicked();
};

#endif // SOCIALS_H
