#include "threadwidget.h"
#include "../../models/usermodel.h"
#include "../../models/threadmodel.h"
#include "../../db/thread_repository.h"

ThreadWidget::ThreadWidget(const QString &userNameText, const QString &postTimeText,
                           const QString &titleText, const QString &contentText,int commentCount, int t_id, QWidget *parent)
    : QWidget(parent),
    threadContainer(new QVBoxLayout()),
    userName(new QLabel(userNameText, this)),
    postTime(new QLabel(postTimeText, this)),
    title(new QLabel(titleText, this)),
    content(new QTextEdit(this)),
    commentIcon(new QLabel(this, "comments:")),
    commentCount(new QLabel(this)),
    postComment(new QPushButton("Post Comment", this)),
    thread_id(t_id)
{
    // Set up widget properties
    userName->setStyleSheet("font-weight: bold; font-size: 14px;");
    postTime->setStyleSheet("font-size: 12px; color: gray;");
    title->setStyleSheet("font-size: 16px; font-weight: bold;");
    content->setReadOnly(true);  // Make the content read-only
    content->setText(contentText);

    // Add widgets to the layout
    threadContainer->addWidget(userName);
    threadContainer->addWidget(postTime);
    threadContainer->addWidget(title);
    threadContainer->addWidget(content);
    threadContainer->addWidget(comment);
    threadContainer->addWidget(postComment);

    // Set the layout for this widget
    setLayout(threadContainer);

    //Connect the postComment button's click signal to a slot
    connect(postComment, &QPushButton::clicked, this, [this]() {
        QString title = this->title->text();
        QString text = this->content->toPlainText();

        UserModel *user = UserModel::getInstance();
        ThreadModel thread(0, title.toStdString(), text.toStdString(), "", user->getId(), -1,thread_id );
        ThreadRepository::addThreadtoDb(thread);
    });
}

ThreadWidget::~ThreadWidget()
{
    delete ui;
}
