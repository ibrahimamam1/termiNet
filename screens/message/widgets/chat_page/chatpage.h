#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include "singleMessage/singlemessage.h"


class ChatPage : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainContainer;
    QScrollArea *chatScrollArea;
    QVBoxLayout *chatContainer;
    QWidget *chatWidget;
    QHBoxLayout *replyLayout;
    QTextEdit *replyTextZone;
    QPushButton *sendBtn;

public:
    explicit ChatPage(QWidget *parent = nullptr);

signals:

private slots:
    void onSendButtonClicked();
};

#endif // CHATPAGE_H
