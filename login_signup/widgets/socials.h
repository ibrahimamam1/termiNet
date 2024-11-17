#ifndef SOCIALS_H
#define SOCIALS_H
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>

class SocialsWidget: public QWidget
{
    QHBoxLayout *container;
    QLabel* googleLogo;
    QLabel* facebookLogo;

public:
    SocialsWidget(QWidget *parent = nullptr);
};

#endif // SOCIALS_H
