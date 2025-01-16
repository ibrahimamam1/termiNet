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
    DividerWidget(QWidget *parent = nullptr){
        container = new QHBoxLayout(this);

        leftLine = new QFrame();
        leftLine->setFrameShape(QFrame::HLine);
        leftLine->setFrameShadow(QFrame::Sunken);

        rightLine = new QFrame();
        rightLine->setFrameShape(QFrame::HLine);
        rightLine->setFrameShadow(QFrame::Sunken);

        QLabel* orLabel = new QLabel("OR Login With");
        orLabel->setAlignment(Qt::AlignCenter);

        container->addWidget(leftLine, 4);
        container->addWidget(orLabel, 2);
        container->addWidget(rightLine, 4);
    }
};

#endif // DIVIDER_H
