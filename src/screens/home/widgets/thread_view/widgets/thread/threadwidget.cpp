#include "threadwidget.h"
#include "../../../../../../models/user/usermodel.h"
#include "../../../../src/models/thread/threadmodel.h"
#include "../../../../../../network/threads/threadrepository.h"
#include "../../home/home.h"

ThreadWidget::ThreadWidget(const ThreadModel& thread, QWidget *parent) : QWidget(parent),
    threadContainer(new QVBoxLayout(this)),
    userName(new QLabel(thread.getAuthor().getName(), this)),
    postTime(new QLabel(thread.getCreatedAt(), this)),
    title(new QLabel(thread.getTitle(), this)),
    content(new QTextEdit(this)),
    commentButton(new QPushButton(this)),
    line(new QFrame()),
    thread_id(thread.getThreadId())
{
    QFont userNameFont;
    userNameFont.setWeight(QFont::DemiBold);
    userNameFont.setUnderline(true);
    userName->setFont(userNameFont);
    userName->setStyleSheet("font-size: 12px; color: gray;");
    postTime->setStyleSheet("font-size: 12px; color: gray;");
    title->setStyleSheet("font-size: 16px; font-weight: bold;");
    content->setReadOnly(true);
    content->setText(thread.getContent());
    content->setStyleSheet("background-color: transparent;");

    // Configure the comment button
    commentButton->setIcon(QIcon("../../assets/comment.png"));
    commentButton->setIconSize(QSize(24, 24)); // Adjust icon size
    commentButton->setText(QString::number(thread.getCommentCount())); // Set the number of comments
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

    //setup horixontal line
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    // Set size policies for widgets
    content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Add widgets to layouts
    threadContainer->addWidget(userName);
    threadContainer->addWidget(postTime);
    threadContainer->addWidget(title);
    threadContainer->addWidget(content); // Ensure it stretches
    threadContainer->addWidget(commentButton);
    threadContainer->addStretch(1);
    threadContainer->addWidget(line);

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
    emit commentIconClicked();
}
