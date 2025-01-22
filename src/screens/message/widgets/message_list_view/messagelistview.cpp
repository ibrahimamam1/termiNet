#include "messagelistview.h"
#include "../message/messagewidget.h"
#include <QDebug>
#include <QPixmap>


MessageListView::MessageListView(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);

    // Search and New Message Bar
    QHBoxLayout *searchBarLayout = new QHBoxLayout();
    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search Messages");
    connect(searchBar, &QLineEdit::returnPressed, this, &MessageListView::onSearchReturnPressed);

    newMessageButton = new ClickableLabel();
    QPixmap pixmap("/home/rgb/Desktop/termiNet/assets/newMessage.png"); // Load the icon for new messages!
    if (pixmap.isNull()) {
        qDebug() << "Failed to load new message icon!";
    }
    newMessageButton->setPixmap(pixmap);
    newMessageButton->setScaledContents(true);
    connect(newMessageButton, &ClickableLabel::clicked, this, &MessageListView::onNewMessageButtonClicked);

    searchBarLayout->addWidget(searchBar);
    searchBarLayout->addWidget(newMessageButton);
    mainLayout->addLayout(searchBarLayout);


    scrollableAreaForMessages = new QScrollArea(this); // Parent to this
    scrollableAreaForMessages->setWidgetResizable(true);
    scrollableAreaForMessages->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollableAreaForMessages->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    messageListContainer = new QWidget();
    messageListLayout = new QVBoxLayout(messageListContainer);
    // messageListLayout->setSpacing(5);
    // messageListLayout->setContentsMargins(10, 10, 10, 10);



    scrollableAreaForMessages->setWidget(messageListContainer);
    mainLayout->addWidget(scrollableAreaForMessages);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MessageListView::setConverstaion(std::vector<MessageModel> messages) {
    // Clear existing messages first
    QLayoutItem* item;
    while ((item = messageListLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    qDebug() << "Setting convos : " << messages.size() << "convos found\n";

    // Add new messages
    for (const auto& message : messages) {
        MessageWidget* msgWidget = new MessageWidget(message, messageListContainer);
        connect(msgWidget, &MessageWidget::conversationClicked,
                this, &MessageListView::onConversationClicked);

        messageListLayout->addWidget(msgWidget);
    }

    // Add stretch at the end
    messageListLayout->addStretch();

    qDebug() << "finished Setting convos : " << messages.size() << "convos set\n";

    // Force layout update
    messageListContainer->updateGeometry();
    scrollableAreaForMessages->updateGeometry();
}
void MessageListView::onNewMessageButtonClicked()
{
    emit newMessageClicked();
}
void MessageListView::onSearchReturnPressed(){
    qDebug() << "search pressed";
}

void MessageListView::onConversationClicked(const UserModel& otherUser) {
    emit conversationClicked(otherUser);
}

