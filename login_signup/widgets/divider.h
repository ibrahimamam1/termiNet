#ifndef DIVIDER_H
#define DIVIDER_H
#include<QWidget>
#include<QFrame>
#include<QLabel>
#include<QHBoxLayout>

class DividerWidget : public QWidget
{
    QHBoxLayout *container;
    QFrame* leftLine;
    QFrame* rightLine;
    QLabel* orLabel;

public:
    DividerWidget(QWidget *parent = nullptr);
};

#endif // DIVIDER_H
