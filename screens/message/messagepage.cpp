#include "messagepage.h"
#include "../../db/message/messagerepository.h"
#include "../../models/user/authenticateduser.h"
MessagePage::MessagePage(QWidget *parent)
    : QWidget{parent}
{
    // Set up main layout
    mainContainer = new QHBoxLayout(this);
    setLayout(mainContainer);

    pages = new QStackedWidget();

    messageListView = new MessageListView(MessageRepository::getMessagesForUser(AuthenticatedUser::getInstance()->getId()), this);
    createNewMessageWidget = new CreateMessage();
    connect(messageListView, &MessageListView::newMessageClicked, this, &MessagePage::switchToCreateNewMessage);


    pages->addWidget(messageListView);
    pages->addWidget(createNewMessageWidget);

    mainContainer->addStretch(1);
    mainContainer->addWidget(pages, 8);
    mainContainer->addStretch(1);

}
void MessagePage::switchToCreateNewMessage(){
    pages->setCurrentIndex(1);
}
