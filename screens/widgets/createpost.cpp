#include "createpost.h"
#include "../../models/usermodel.h"

CreatePost::CreatePost(QWidget *parent)
    : QWidget{parent}
{

    mainContainer = new QVBoxLayout(this);
    titleArea = new QLineEdit("Enter Title");
    textArea = new QTextEdit();
    postBtn = new QPushButton("Post");

    mainContainer->addWidget(titleArea, 2);
    mainContainer->addWidget(textArea, 6);
    mainContainer->addWidget(postBtn, 2);

    connect(this->postBtn, &QPushButton::clicked, this, &CreatePost::on_postBtn_clicked);

    threadRepo = new ThreadRepository();
}
void CreatePost::on_postBtn_clicked()
{
    qDebug() << "Going to send a post to db yaaay";
    QString title = this->titleArea->text();
    QString text = this->textArea->toPlainText();

    UserModel *user = UserModel::getInstance();
    ThreadModel thread(0, title.toStdString(), text.toStdString(), "", user->getId(), -1, -1);
    threadRepo->addThreadtoDb(thread);


}
