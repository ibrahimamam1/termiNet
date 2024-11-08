/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *login_email;
    QLabel *label_2;
    QLineEdit *login_pass;
    QPushButton *login_btn;
    QLabel *forgot_password_label;
    QLabel *create_account_label;
    QLabel *label_5;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(400, 300);
        formLayoutWidget = new QWidget(Login);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(100, 50, 160, 80));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        login_email = new QLineEdit(formLayoutWidget);
        login_email->setObjectName("login_email");

        formLayout->setWidget(0, QFormLayout::FieldRole, login_email);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        login_pass = new QLineEdit(formLayoutWidget);
        login_pass->setObjectName("login_pass");

        formLayout->setWidget(1, QFormLayout::FieldRole, login_pass);

        login_btn = new QPushButton(formLayoutWidget);
        login_btn->setObjectName("login_btn");

        formLayout->setWidget(2, QFormLayout::SpanningRole, login_btn);

        forgot_password_label = new QLabel(Login);
        forgot_password_label->setObjectName("forgot_password_label");
        forgot_password_label->setGeometry(QRect(120, 150, 151, 16));
        create_account_label = new QLabel(Login);
        create_account_label->setObjectName("create_account_label");
        create_account_label->setGeometry(QRect(120, 170, 131, 16));
        label_5 = new QLabel(Login);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(120, 210, 131, 16));
        line = new QFrame(Login);
        line->setObjectName("line");
        line->setGeometry(QRect(220, 210, 131, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(Login);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(-10, 210, 101, 16));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Login", "Email :", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "Password:", nullptr));
        login_btn->setText(QCoreApplication::translate("Login", "Login", nullptr));
        forgot_password_label->setText(QCoreApplication::translate("Login", "Forgot Password?", nullptr));
        create_account_label->setText(QCoreApplication::translate("Login", "Create Account", nullptr));
        label_5->setText(QCoreApplication::translate("Login", "Continue With", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
