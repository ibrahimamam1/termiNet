/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_12;
    QFrame *line;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName("Home");
        Home->resize(1267, 688);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Home->sizePolicy().hasHeightForWidth());
        Home->setSizePolicy(sizePolicy);
        Home->setMinimumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("Ubuntu")});
        Home->setFont(font);
        centralwidget = new QWidget(Home);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(30, 30, 1211, 481));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout->addWidget(label_4);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 5);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName("label_9");

        verticalLayout_8->addWidget(label_9);

        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName("label_10");

        verticalLayout_8->addWidget(label_10);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName("label_8");

        verticalLayout_8->addWidget(label_8);


        verticalLayout_5->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_12 = new QLabel(verticalLayoutWidget);
        label_12->setObjectName("label_12");

        verticalLayout_7->addWidget(label_12);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_7->addWidget(line);

        label_13 = new QLabel(verticalLayoutWidget);
        label_13->setObjectName("label_13");

        verticalLayout_7->addWidget(label_13);

        label_14 = new QLabel(verticalLayoutWidget);
        label_14->setObjectName("label_14");

        verticalLayout_7->addWidget(label_14);

        label_15 = new QLabel(verticalLayoutWidget);
        label_15->setObjectName("label_15");

        verticalLayout_7->addWidget(label_15);

        label_11 = new QLabel(verticalLayoutWidget);
        label_11->setObjectName("label_11");

        verticalLayout_7->addWidget(label_11);


        verticalLayout_5->addLayout(verticalLayout_7);

        verticalLayout_5->setStretch(0, 4);
        verticalLayout_5->setStretch(1, 6);

        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");

        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName("label_6");

        verticalLayout_6->addWidget(label_6);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName("label_7");

        verticalLayout_6->addWidget(label_7);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout_6->addWidget(label_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_6);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 6);
        horizontalLayout_2->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 9);
        Home->setCentralWidget(centralwidget);

        retranslateUi(Home);

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QMainWindow *Home)
    {
        Home->setWindowTitle(QCoreApplication::translate("Home", "TermiNet", nullptr));
        label_4->setText(QCoreApplication::translate("Home", "logo", nullptr));
        label_3->setText(QCoreApplication::translate("Home", "search", nullptr));
        label_2->setText(QCoreApplication::translate("Home", "message", nullptr));
        label->setText(QCoreApplication::translate("Home", "profile", nullptr));
        label_9->setText(QCoreApplication::translate("Home", "Home", nullptr));
        label_10->setText(QCoreApplication::translate("Home", "Popular", nullptr));
        label_8->setText(QCoreApplication::translate("Home", "Explore", nullptr));
        label_12->setText(QCoreApplication::translate("Home", "Your Communities", nullptr));
        label_13->setText(QCoreApplication::translate("Home", "community 1", nullptr));
        label_14->setText(QCoreApplication::translate("Home", "community 2", nullptr));
        label_15->setText(QCoreApplication::translate("Home", "community 3", nullptr));
        label_11->setText(QCoreApplication::translate("Home", "community 4", nullptr));
        label_6->setText(QCoreApplication::translate("Home", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("Home", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("Home", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
