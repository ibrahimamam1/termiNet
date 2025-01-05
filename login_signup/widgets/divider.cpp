#include "divider.h"

DividerWidget::DividerWidget(QWidget *parent) {

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
