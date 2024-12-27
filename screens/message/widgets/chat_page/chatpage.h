#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include "singleMessage/singlemessage.h"
#include "../../../../models/user/usermodel.h"


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
    void setOtherUser(const UserModel& u);
    UserModel getOtherUser() const;

signals:

private slots:
    void onSendButtonClicked();

private:
    UserModel otherUser;
};

#endif // CHATPAGE_H
