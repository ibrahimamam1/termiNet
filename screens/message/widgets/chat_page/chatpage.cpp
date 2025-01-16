#include "chatpage.h"
#include "../../../../helpers/websocket_client/websocketclient.h"
#include "../../../../src/db/manager/databasemanager.h"
#include "../../../../src/models/user/authenticateduser.h"
#include <QScrollBar>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox> // For displaying error messages

ChatPage::ChatPage(QWidget *parent)
    : QWidget{parent}
{
    chatScrollArea = new QScrollArea();
    chatScrollArea->setWidgetResizable(true);
    chatScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chatScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    chatWidget = new QWidget();
    chatContainer = new QVBoxLayout(chatWidget);
    chatWidget->setLayout(chatContainer);

    chatScrollArea->setWidget(chatWidget);

    replyLayout = new QHBoxLayout();
    replyTextZone = new QTextEdit();
    replyTextZone->setPlaceholderText("Enter Message...");
    sendBtn = new QPushButton("send");
    connect(sendBtn, &QPushButton::clicked, this, &ChatPage::onSendButtonClicked);
    replyLayout->addWidget(replyTextZone);
    replyLayout->addWidget(sendBtn);

    mainContainer = new QVBoxLayout(this);
    mainContainer->addWidget(chatScrollArea);
    mainContainer->addLayout(replyLayout);

    setLayout(mainContainer);
}

void ChatPage::onSendButtonClicked(){
    qDebug() << "Going to send message";
    QString text = replyTextZone->toPlainText();
    if (text.isEmpty()) return;

    QDateTime timestamp = QDateTime::currentDateTime();
    MessageModel msg(otherUser, text, timestamp);

    WebSocketClient& websocket = WebSocketClient::getInstance();
    DatabaseManager& db = DatabaseManager::getInstance();

    try{
        QJsonObject messageJson;
        messageJson["type"] = 2;
        messageJson["source"] = AuthenticatedUser::getInstance()->getId();
        messageJson["destination"] = otherUser.getId();
        messageJson["content"] = text;

        QJsonDocument jsonDoc(messageJson);
        QString payload = jsonDoc.toJson(QJsonDocument::Compact);

        websocket.sendMessage(payload);
        db.addOutgoingMessage(msg);
        SingleMessage *messageWidget = new SingleMessage(msg, 2, this);
        chatContainer->addWidget(messageWidget);
        replyTextZone->clear();
        updateUi();

    } catch (const std::exception& e) {
        qDebug() << "Failed to send message: " << e.what();
        QMessageBox::critical(this, "Error Sending Message", QString("Failed to send message: ") + e.what());
    } catch (...) {
        qDebug() << "Failed to send message: An unknown error occurred.";
        QMessageBox::critical(this, "Error Sending Message", "Failed to send message: An unknown error occurred.");
    }
}

void ChatPage::setOtherUser(const UserModel& u){
    otherUser = u;
}

UserModel ChatPage::getOtherUser() const{
    return otherUser;
}

void ChatPage::setMessages(std::vector<MessageModel> msgs){
    // Clear existing messages before setting new ones
    QLayoutItem *item;
    while ((item = chatContainer->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    messages = msgs;

    for(const auto& message : messages){
        int direction = message.getOtherUser().getId() == AuthenticatedUser::getInstance()->getId() ? 1 : 2;
        SingleMessage *messageWidget = new SingleMessage(message, direction, this);
        chatContainer->addWidget(messageWidget);
    }
     qDebug() << "You should see " << messages.size() << " messages";
    updateUi();
}

void ChatPage::addMessage(MessageModel m){
    messages.push_back(m);
    SingleMessage *messageWidget = new SingleMessage(m, 1, this); //direction is set to 1 because this function is only called when a message is received
    chatContainer->addWidget(messageWidget);
}

void ChatPage::updateUi(){
    chatScrollArea->verticalScrollBar()->setValue(chatScrollArea->verticalScrollBar()->maximum());
}
