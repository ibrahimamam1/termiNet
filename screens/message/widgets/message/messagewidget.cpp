#include "messagewidget.h"
#include "../../../../src/models/user/authenticateduser.h"
#include <QMouseEvent>

MessageWidget::MessageWidget(const MessageModel& msg, QWidget *parent) :message(msg), QWidget{parent}
{


    mainLayout = new QVBoxLayout(this);
    QString otherUserName = msg.getOtherUser().getName();
    userName = new QLabel(otherUserName);
    preview = new QLineEdit();
    preview->setReadOnly(true);

    // Safe way to handle message preview
    QString content = msg.getMessageContent();
    QString previewText;
    if (content.length() > 10) {
        previewText = content.left(10) + "...";
    } else {
        previewText = content;
    }
    preview->setText(previewText);

    mainLayout->addWidget(userName);
    mainLayout->addWidget(preview);

    // Make the widget look clickable
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("MessageWidget { background-color: transparent; }"
                  "MessageWidget:hover { background-color: #f0f0f0; }");

    // Enable mouse tracking for hover effects
    setMouseTracking(true);
}

void MessageWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit conversationClicked(message.getOtherUser());
    }
    QWidget::mousePressEvent(event);
}
