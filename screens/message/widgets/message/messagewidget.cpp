#include "messagewidget.h"
#include "../../../../models/user/authenticateduser.h"

MessageWidget::MessageWidget(const MessageModel& msg, QWidget *parent) : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);

    QString otherUserName = AuthenticatedUser::getInstance()->getId() == msg.getSender().getId() ? msg.getReceiver().getName() : msg.getSender().getName();
    userName = new QLabel(otherUserName);
    preview = new QLineEdit();
    preview->setReadOnly(true);
    preview->setPlaceholderText(msg.getMessagePreview());

    mainLayout->addWidget(userName);
    mainLayout->addWidget(preview);

}
