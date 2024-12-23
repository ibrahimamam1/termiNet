#include "chatpage.h"

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
    qDebug() << "Sending a message baby";
}
