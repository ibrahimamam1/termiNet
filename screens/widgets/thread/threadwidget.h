#ifndef THREADWIDGET_H
#define THREADWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QTextEdit>
#include<QPushButton>
#include"../../../models/thread/threadmodel.h"

class ThreadWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *threadContainer;
    QLabel *userName;
    QLabel *postTime;
    QLabel *title;
    QTextEdit *content;
    QPushButton *commentButton;
    QFrame *line;
    int thread_id;

public:
    explicit ThreadWidget(const ThreadModel& thread, QWidget *parent = nullptr );

    QString getUserName() const;
    QString getPostTime() const;
    QString getTitle() const;
    QString getContent() const;
    int getCommentCount() const;
    int getThreadId() const;

    ~ThreadWidget();

signals:
    void switchToCommentScreen(int parentThreadId);

private:

private slots:
    void onCommentButtonClicked();

};

#endif // THREADWIDGET_H
