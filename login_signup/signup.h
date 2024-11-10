#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "../db/databasemanager.h"

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT
    DatabaseManager *db;

public:
   explicit Signup(QWidget *parent, DatabaseManager* instance);
    bool validate_signup_form(std::string name ,std::string email ,std::string sex ,std::string dob ,std::string pass,std::string pass2);
   void readUserTable();
   ~Signup();

private slots:
    void on_create_account_btn_clicked();

private:
    Ui::Signup *ui;
};

#endif // SIGNUP_H
