#include "divider.h"

DividerWidget::DividerWidget(QWidget *parent) {

    container = new QHBoxLayout();

    leftLine = new QFrame(parent);
    leftLine->setFrameShape(QFrame::HLine);
    leftLine->setFrameShadow(QFrame::Sunken);

    rightLine = new QFrame(parent);
    rightLine->setFrameShape(QFrame::HLine);
    rightLine->setFrameShadow(QFrame::Sunken);

    QLabel* orLabel = new QLabel("OR", parent);
    orLabel->setAlignment(Qt::AlignCenter);

    container->addWidget(leftLine, 4);
    container->addWidget(orLabel, 2);
    container->addWidget(rightLine, 4);
}
