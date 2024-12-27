#include "singlemessage.h"

SingleMessage::SingleMessage(const MessageModel& msg,int direction, QWidget *parent)
    : m_msg(msg), m_direction(direction), QWidget{parent}
{
    mainContainer = new QHBoxLayout(this);
    messageText = new QLineEdit(m_msg.getMessageContent());
    messageText->setReadOnly(true);

    if(direction == 1){
        mainContainer->addWidget(messageText);
        mainContainer->addStretch();
    }else{
        mainContainer->addStretch();
        mainContainer->addWidget(messageText);
    }

}
