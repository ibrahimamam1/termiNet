#ifndef REPLYBOX_H
#define REPLYBOX_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class ReplyBox : public QWidget
{
    Q_OBJECT
    QVBoxLayout *replyContainer;
    QTextEdit *reply;
    QHBoxLayout *replyButtonContainer;
    QPushButton *replyButton;

    int currentThreadId;

public:
    explicit ReplyBox(QWidget *parent = nullptr);
    void setCurrentThreadId(int id);

signals:
};

#endif // REPLYBOX_H
