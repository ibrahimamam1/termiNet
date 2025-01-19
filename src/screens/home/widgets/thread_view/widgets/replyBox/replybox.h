#ifndef REPLYBOX_H
#define REPLYBOX_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include "../../../../../../models/thread/threadmodel.h"

class ReplyBox : public QWidget
{
    Q_OBJECT
    QVBoxLayout *replyContainer;
    QTextEdit *reply;
    QHBoxLayout *replyButtonContainer;
    QPushButton *replyButton;

    ThreadModel parentThread;

public:
    explicit ReplyBox(QWidget *parent = nullptr);
    void setParentThread(const ThreadModel& parent);

signals:
};

#endif // REPLYBOX_H
