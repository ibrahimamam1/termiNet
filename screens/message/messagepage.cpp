#include "messagepage.h"
#include "../../db/message/messagerepository.h"
#include "../../models/user/authenticateduser.h"
#include "../../screens/home/home.h"
#include "../../src/db/manager/databasemanager.h"
#include <algorithm>

MessagePage::MessagePage(QWidget *parent)
    : QWidget{parent}
{
    // Set up main layout
    mainContainer = new QHBoxLayout(this);
    setLayout(mainContainer);

    pages = new QStackedWidget();

    messageListView = new MessageListView(MessageRepository::getSentMessagesForUser(AuthenticatedUser::getInstance()->getId()), this);
    connect(messageListView, &MessageListView::newMessageClicked, this, &MessagePage::switchToCreateNewMessage);

    createNewMessageWidget = new CreateMessage();
    connect(createNewMessageWidget, &CreateMessage::userSelected, this, &MessagePage::switchToChatScreen);

    chatPage = new ChatPage();


    pages->addWidget(messageListView);
    pages->addWidget(createNewMessageWidget);
    pages->addWidget(chatPage);

    mainContainer->addStretch(1);
    mainContainer->addWidget(pages, 8);
    mainContainer->addStretch(1);

}
void MessagePage::switchToCreateNewMessage(){
    pages->setCurrentIndex(1);
}

void MessagePage::switchToChatScreen(){
    qDebug() << "Switching to chat Screen for receiver" << createNewMessageWidget->getReceiver().getName();

    //get all messages exchange with other user
    DatabaseManager& db = DatabaseManager::getInstance();
    std::vector<MessageModel>sentMessages = db.getSentMessagesTo(createNewMessageWidget->getReceiver().getId());
    std::vector<MessageModel>receivedMessages = db.getReceivedMessagesFrom(createNewMessageWidget->getReceiver().getId());
    //todo: merge two vectors
    std::vector<MessageModel> allMessages;
    allMessages.insert(allMessages.end(), sentMessages.begin(), sentMessages.end());
    allMessages.insert(allMessages.end(), receivedMessages.begin(), receivedMessages.end());

    // Sort the merged vector based on the timestamp
    std::sort(allMessages.begin(), allMessages.end(), [](const MessageModel& a, const MessageModel& b) {
        return a.getTimestamp() < b.getTimestamp();
    });

    chatPage->setOtherUser(createNewMessageWidget->getReceiver());
    chatPage->setMessages(allMessages);

    pages->setCurrentIndex(2);
}
