#include "replybox.h"
#include "../../../../../../models/user/authenticateduser.h"
#include "../../../../../../models/thread/threadmodel.h"
#include "../../../../../../network/threads/threadrepository.h"

ReplyBox::ReplyBox(QWidget *parent)
    : QWidget{parent}
{
    replyContainer = new QVBoxLayout(this);

    //setup reply box
    reply = new QTextEdit();
    reply->setPlaceholderText("Your Reply...");

    replyButtonContainer = new QHBoxLayout();
    replyButton = new QPushButton("Post");

    connect(replyButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "Yup you want to comment a thread huh";
        QString title = "reply to " + parentThread.getAuthor().getName();
        QString text = reply->toPlainText();

        UserModel& user = AuthenticatedUser::getInstance();
        ThreadModel thread(title, text, user, parentThread.getCommunityId(), parentThread.getThreadId());
        ThreadRepository::postNewThread(thread);

        reply->clear();
    });

    replyButtonContainer->addStretch(2);
    replyButtonContainer->addWidget(replyButton, 1);
    replyButtonContainer->addStretch(2);

    replyContainer->addWidget(reply, 3);
    replyContainer->addLayout(replyButtonContainer, 2);
}

void ReplyBox::setParentThread(const ThreadModel& parent){
    parentThread = parent;
}
