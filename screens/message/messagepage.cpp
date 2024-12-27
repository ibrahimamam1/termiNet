#include "messagepage.h"
#include "../../db/message/messagerepository.h"
#include "../../models/user/authenticateduser.h"
#include "../../screens/home/home.h"

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
    chatPage->setOtherUser(createNewMessageWidget->getReceiver());
    pages->setCurrentIndex(2);

}
