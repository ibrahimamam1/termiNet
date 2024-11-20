#ifndef THREADWIDGET_H
#define THREADWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QTextEdit>
#include<QPushButton>

class ThreadWidget : public QWidget
{
    Q_OBJECT
    QVBoxLayout *threadContainer;
    QLabel *userName;
    QLabel *postTime;
    QLabel *title;
    QTextEdit *content;
    QPushButton *commentButton;
    int thread_id;

public:
    explicit ThreadWidget(const QString &userNameText, const QString &postTimeText,
                          const QString &titleText, const QString &contentText, int comment_count, int t_id, QWidget *parent = nullptr);

    QString getUserName() const;
    QString getPostTime() const;
    QString getTitle() const;
    QString getContent() const;
    int getCommentCount() const;
    int getThreadId() const;

    ~ThreadWidget();

signals:
    void switchToCommentScreen(int threadId);

private:

private slots:
    void onCommentButtonClicked();

};

#endif // THREADWIDGET_H
