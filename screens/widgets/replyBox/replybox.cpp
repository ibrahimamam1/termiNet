#include "replybox.h"
#include "../../../src/models/user/authenticateduser.h"
#include "../../../models/thread/threadmodel.h"
#include "../../../db/thread/thread_repository.h"

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
        QString title = "";
        QString text = reply->toPlainText();

        UserModel *user = AuthenticatedUser::getInstance();
        ThreadModel thread(0, title, text,0, "", *user, -1, currentThreadId);
        ThreadRepository::addThreadtoDb(thread);

        reply->clear();
    });

    replyButtonContainer->addStretch(2);
    replyButtonContainer->addWidget(replyButton, 1);
    replyButtonContainer->addStretch(2);

    replyContainer->addWidget(reply, 3);
    replyContainer->addLayout(replyButtonContainer, 2);
}

void ReplyBox::setCurrentThreadId(int id){
    currentThreadId = id;
}
