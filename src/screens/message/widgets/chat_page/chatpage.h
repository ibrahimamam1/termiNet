#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include "single_message/singlemessage.h"
#include "../../../../src/models/user/usermodel.h"


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
    void setMessages(std::vector<MessageModel>msgs);
    void addMessage(MessageModel m);
    void updateUi();

signals:

private slots:
    void onSendButtonClicked();

private:
    UserModel otherUser;
    std::vector<MessageModel> messages;
};

#endif // CHATPAGE_H
