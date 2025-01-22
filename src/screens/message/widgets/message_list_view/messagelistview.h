#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include "../../../../src/common/widgets/clickable_label.h"
#include "../../../../src/models/message/messagemodel.h"

class MessageListView : public QWidget
{
    Q_OBJECT
    QScrollArea *scrollableAreaForMessages; //area on which message previes will be shown
    QWidget *messageListContainer;
    QVBoxLayout *mainLayout; // Main layout for search bar and new message
    QVBoxLayout *messageListLayout;
    QLineEdit *searchBar;
    ClickableLabel *newMessageButton;

public:
    explicit MessageListView(QWidget *parent = nullptr);
    void setConverstaion(std::vector<MessageModel> messages);
    void updateMessages(const std::vector<MessageModel>& newMessages);

private slots:
    void onNewMessageButtonClicked();
    void onSearchReturnPressed();
    void onConversationClicked(const UserModel& otherUser);

signals:
    void newMessageClicked();
    void conversationClicked(const UserModel& otherUser);
};

#endif // MESSAGELISTVIEW_H
