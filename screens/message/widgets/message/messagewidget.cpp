#include "messagewidget.h"
#include "../../../../src/models/user/authenticateduser.h"

MessageWidget::MessageWidget(const MessageModel& msg, QWidget *parent) : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);

    QString otherUserName = "yolo";
    userName = new QLabel(otherUserName);
    preview = new QLineEdit();
    preview->setReadOnly(true);
    preview->setPlaceholderText(msg.getMessageContent().chopped(10));

    mainLayout->addWidget(userName);
    mainLayout->addWidget(preview);

}
