#ifndef MESSAGEPAGE_H
#define MESSAGEPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QScrollArea>
#include <QSplitter>
#include "widgets/message_list_view/messagelistview.h"
#include "widgets/create_message/createmessage.h"
#include "widgets/chat_page/chatpage.h"


class MessagePage : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    QStackedWidget *pages;

    CreateMessage *createNewMessageWidget;
    ChatPage *chatPage;
    //NewMessageWidget *newMessageWidget;

public:
    MessageListView *messageListView;
    explicit MessagePage(QWidget *parent = nullptr);
    void switchToCreateNewMessage();


signals:

public slots:
    void onMessageReceived(const QString& msg);
    void switchToChatScreen(const UserModel& otherUser);

private:
};

#endif // MESSAGEPAGE_H
