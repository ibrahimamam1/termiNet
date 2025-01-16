#include "messagepage.h"
#include "../../db/message/messagerepository.h"
#include "../../src/models/user/authenticateduser.h"
#include "../../src/network/user/user_repository.h"
#include "../../screens/home/home.h"
#include "../../src/db/manager/databasemanager.h"
#include <algorithm>
#include <QJsonDocument>
#include <QJsonObject>

MessagePage::MessagePage(QWidget *parent)
    : QWidget{parent}
{
    // Set up main layout
    mainContainer = new QHBoxLayout(this);
    setLayout(mainContainer);

    pages = new QStackedWidget();

    messageListView = new MessageListView(this);
    qDebug() << "Init Message List View";
    connect(messageListView, &MessageListView::newMessageClicked, this, &MessagePage::switchToCreateNewMessage);
    connect(messageListView, &MessageListView::conversationClicked, this, &MessagePage::switchToChatScreen);

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

void MessagePage::switchToChatScreen(const UserModel& otherUser){
    qDebug() << "Switching to chat Screen for receiver" << otherUser.getId();

    //get all messages exchange with other user
    DatabaseManager& db = DatabaseManager::getInstance();
    std::vector<MessageModel>sentMessages = db.getSentMessagesTo(otherUser.getId());
    std::vector<MessageModel>receivedMessages = db.getReceivedMessagesFrom(otherUser.getId());
    //todo: merge two vectors
    std::vector<MessageModel> allMessages;
    allMessages.insert(allMessages.end(), sentMessages.begin(), sentMessages.end());
    allMessages.insert(allMessages.end(), receivedMessages.begin(), receivedMessages.end());

    // Sort the merged vector based on the timestamp
    std::sort(allMessages.begin(), allMessages.end(), [](const MessageModel& a, const MessageModel& b) {
        return a.getTimestamp() < b.getTimestamp();
    });

    chatPage->setOtherUser(otherUser);
    chatPage->setMessages(allMessages);

    pages->setCurrentIndex(2);
}

void MessagePage::onMessageReceived(const QString& msg) {
    qDebug() << "Inside message page, received message:" << msg;

    // Parse the JSON string
    QJsonDocument jsonDoc = QJsonDocument::fromJson(msg.toUtf8());
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to parse JSON message";
        return;
    }

    // Convert to a JSON object
    QJsonObject jsonObj = jsonDoc.object();

    // Extract the sender id and message string
    if (jsonObj.contains("sender_id") && jsonObj.contains("message")) {
        QString sender_id = jsonObj["sender_id"].toString();
        QString message = jsonObj["message"].toString();

        qDebug() << "Received message from :" << sender_id;
        qDebug() << "message:" << message;

        UserModel sender = UserRepository::getUserFromId(sender_id);
        QDateTime now = QDateTime::currentDateTime();
        MessageModel m(sender, message, now);
        chatPage->addMessage(m);

        DatabaseManager db = DatabaseManager::getInstance();
        db.addIncomingMessage(m);

    } else {
        qDebug() << "JSON message is missing required fields";
    }
}

