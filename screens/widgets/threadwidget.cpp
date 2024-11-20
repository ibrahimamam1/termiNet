#include "threadwidget.h"
#include "../../models/usermodel.h"
#include "../../models/threadmodel.h"
#include "../../db/thread_repository.h"

ThreadWidget::ThreadWidget(const QString &userNameText, const QString &postTimeText,
                           const QString &titleText, const QString &contentText,
                           int c_count, int t_id, QWidget *parent)
    : QWidget(parent),
    threadContainer(new QVBoxLayout(this)),
    userName(new QLabel(userNameText, this)),
    postTime(new QLabel(postTimeText, this)),
    title(new QLabel(titleText, this)),
    content(new QTextEdit(this)),
    commentButton(new QPushButton(this)),
    thread_id(t_id)
{
    // Set up styles
    userName->setStyleSheet("font-weight: bold; font-size: 14px;");
    postTime->setStyleSheet("font-size: 12px; color: gray;");
    title->setStyleSheet("font-size: 16px; font-weight: bold;");
    content->setReadOnly(true);
    content->setText(contentText);

    // Configure the comment button
    commentButton->setIcon(QIcon(":/path/to/comment_icon.png")); // Replace with your icon path
    commentButton->setIconSize(QSize(24, 24)); // Adjust icon size
    commentButton->setText(QString::number(c_count)); // Set the number of comments
    commentButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    connect(commentButton, &QPushButton::clicked, this, &ThreadWidget::onCommentButtonClicked);

    // Style the button
    commentButton->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    background: transparent;"
        "    text-align: center;"
        "    font-size: 12px;"
        "    color: gray;"
        "}"
        "QPushButton:hover {"
        "    color: #3498db;" // Change color on hover
        "}"
        );

    // Ensure icon and text are vertically aligned
    //commentButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // Set size policies for widgets
    content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Add widgets to layouts
    threadContainer->addWidget(userName);
    threadContainer->addWidget(postTime);
    threadContainer->addWidget(title);
    threadContainer->addWidget(content); // Ensure it stretches
    threadContainer->addWidget(commentButton);

    // Set layout for the widget
    setLayout(threadContainer);
}

QString ThreadWidget::getUserName() const{ return userName->text(); }
QString ThreadWidget::getPostTime() const {return postTime->text(); }
QString ThreadWidget::getTitle() const {return title->text();}
QString ThreadWidget::getContent() const {return content->toPlainText();}
int ThreadWidget::getCommentCount() const {return commentButton->text().toInt();}
int ThreadWidget::getThreadId() const {return thread_id; }

ThreadWidget::~ThreadWidget()
{

}

void ThreadWidget::onCommentButtonClicked()
{
    qDebug() << "Yup, you clicked on Comments for thread ID:" << thread_id;
    emit switchToCommentScreen(thread_id);
}
