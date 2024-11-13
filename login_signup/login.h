#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlError>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_login_btn_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
