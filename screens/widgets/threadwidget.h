#ifndef THREADWIDGET_H
#define THREADWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QTextEdit>
#include<QPushButton>

namespace Ui {
class ThreadWidget;
}

class ThreadWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *threadContainer;
    QLabel *userName;
    QLabel *postTime;
    QLabel *title;
    QTextEdit *content;
    QLabel *commentIcon;
    QLabel *commentCount;
    QPushButton *postComment;
    int thread_id;

public:
    explicit ThreadWidget(const QString &userNameText, const QString &postTimeText,
                          const QString &titleText, const QString &contentText, int comment_count, int t_id, QWidget *parent = nullptr);
    ~ThreadWidget();

private:
    Ui::ThreadWidget *ui;

};

#endif // THREADWIDGET_H
