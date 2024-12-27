#include "chatpage.h"
#include "../../../../helpers/websocket_client/websocketclient.h"
#include "../../../../src/db/manager/databasemanager.h"

ChatPage::ChatPage(QWidget *parent)
    : QWidget{parent}
{
    chatScrollArea = new QScrollArea();
    chatScrollArea->setWidgetResizable(true);
    chatScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chatScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    chatWidget = new QWidget();
    chatContainer = new QVBoxLayout(chatWidget);

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
}

void ChatPage::onSendButtonClicked(){
    qDebug() << "Going to send message";
    QString text = replyTextZone->toPlainText();
    QDateTime timestamp = QDateTime::currentDateTime();
    MessageModel msg(otherUser, text, timestamp);

    WebSocketClient& websocket = WebSocketClient::getInstance();
    try{
        websocket.sendMessage(text);
        DatabaseManager& db = DatabaseManager::getInstance();
        db.addOutgoingMessage(msg);

    }catch(std::exception e){
        qDebug() << "Failed to send message : " << e.what();

    }

}

void ChatPage::setOtherUser(const UserModel& u){
    otherUser = u;
}
UserModel ChatPage::getOtherUser() const{
    return otherUser;
}
