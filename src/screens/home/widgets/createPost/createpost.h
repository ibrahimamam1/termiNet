#ifndef CREATEPOST_H
#define CREATEPOST_H

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpacerItem>
#include <QFrame>
#include <QPushButton>
#include <QSqlQuery>
#include "../../../../src/models/thread/threadmodel.h"
#include "../../../../network/threads/threadrepository.h"

class CreatePost : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainContainer;
    QLineEdit *titleArea;
    QTextEdit *textArea;
    QPushButton *postBtn;


public:
    explicit CreatePost(QWidget *parent = nullptr);
private slots:
    void onPostBtnClicked();

signals:
    void postCreated(bool success);
};

#endif // CREATEPOST_H
