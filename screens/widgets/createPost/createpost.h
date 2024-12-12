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
#include "../../../models/thread/threadmodel.h"
#include "../../../db/thread_repository.h"

class CreatePost : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainContainer;
    QLineEdit *titleArea;
    QTextEdit *textArea;
    QPushButton *postBtn;

    ThreadRepository *threadRepo;


public:
    explicit CreatePost(QWidget *parent = nullptr);
private slots:
    void on_postBtn_clicked();

signals:
};

#endif // CREATEPOST_H
