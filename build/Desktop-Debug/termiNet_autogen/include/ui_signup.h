/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Signup
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *user_name;
    QLabel *label_3;
    QLineEdit *user_email;
    QLabel *label_5;
    QLineEdit *user_sex;
    QLabel *label_4;
    QLineEdit *user_dob;
    QLabel *label_2;
    QLineEdit *user_pass;
    QLabel *label_6;
    QLineEdit *user_comfirm_pass;
    QPushButton *create_account_btn;

    void setupUi(QDialog *Signup)
    {
        if (Signup->objectName().isEmpty())
            Signup->setObjectName("Signup");
        Signup->resize(484, 637);
        formLayoutWidget = new QWidget(Signup);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(130, 90, 291, 241));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        user_name = new QLineEdit(formLayoutWidget);
        user_name->setObjectName("user_name");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, user_name);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        user_email = new QLineEdit(formLayoutWidget);
        user_email->setObjectName("user_email");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, user_email);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName("label_5");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        user_sex = new QLineEdit(formLayoutWidget);
        user_sex->setObjectName("user_sex");

        formLayout_2->setWidget(2, QFormLayout::FieldRole, user_sex);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);

        user_dob = new QLineEdit(formLayoutWidget);
        user_dob->setObjectName("user_dob");

        formLayout_2->setWidget(3, QFormLayout::FieldRole, user_dob);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_2);

        user_pass = new QLineEdit(formLayoutWidget);
        user_pass->setObjectName("user_pass");

        formLayout_2->setWidget(4, QFormLayout::FieldRole, user_pass);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName("label_6");

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_6);

        user_comfirm_pass = new QLineEdit(formLayoutWidget);
        user_comfirm_pass->setObjectName("user_comfirm_pass");

        formLayout_2->setWidget(5, QFormLayout::FieldRole, user_comfirm_pass);

        create_account_btn = new QPushButton(formLayoutWidget);
        create_account_btn->setObjectName("create_account_btn");

        formLayout_2->setWidget(6, QFormLayout::SpanningRole, create_account_btn);


        retranslateUi(Signup);

        QMetaObject::connectSlotsByName(Signup);
    } // setupUi

    void retranslateUi(QDialog *Signup)
    {
        Signup->setWindowTitle(QCoreApplication::translate("Signup", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Signup", "User Name :", nullptr));
        label_3->setText(QCoreApplication::translate("Signup", "Email", nullptr));
        label_5->setText(QCoreApplication::translate("Signup", "Sex", nullptr));
        label_4->setText(QCoreApplication::translate("Signup", "Date of Birth", nullptr));
        label_2->setText(QCoreApplication::translate("Signup", "Password", nullptr));
        label_6->setText(QCoreApplication::translate("Signup", "Comfirm Password", nullptr));
        create_account_btn->setText(QCoreApplication::translate("Signup", "Create Account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Signup: public Ui_Signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
