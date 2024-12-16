#ifndef MESSAGEPAGE_H
#define MESSAGEPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QScrollArea>
#include <QSplitter>
#include "widgets/message_list_view/messagelistview.h"
#include "widgets/create_message/createmessage.h"

class MessagePage : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    QStackedWidget *pages;
    MessageListView *messageListView;
    CreateMessage *createNewMessageWidget;
    QWidget *chatContainer;
    QSplitter *chatLayout;
    QScrollArea *scrollableAreaForChats;
    //NewMessageWidget *newMessageWidget;


public:
    explicit MessagePage(QWidget *parent = nullptr);
    void switchToCreateNewMessage();

signals:
};

#endif // MESSAGEPAGE_H
