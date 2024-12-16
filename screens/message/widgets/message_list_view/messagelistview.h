#ifndef MESSAGELISTVIEW_H
#define MESSAGELISTVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include "../../../widgets/clickablelabel.h"
#include "../../../../models/message/messagemodel.h"

class MessageListView : public QWidget
{
    Q_OBJECT
    QScrollArea *scrollableAreaForMessages; //area on which message previes will be shown
    QWidget *messageListContainer;
    QVBoxLayout *mainLayout; // Main layout for search bar and new message
    QVBoxLayout *messageListLayout;
    std::vector<MessageModel> messages;
    QLineEdit *searchBar;
    ClickableLabel *newMessageButton;

public:
    explicit MessageListView(std::vector<MessageModel> msgs, QWidget *parent = nullptr);
    void updateMessages(const std::vector<MessageModel>& newMessages);

private slots:
    void onNewMessageButtonClicked();
    void onSearchReturnPressed();

signals:
    void newMessageClicked();
};

#endif // MESSAGELISTVIEW_H
