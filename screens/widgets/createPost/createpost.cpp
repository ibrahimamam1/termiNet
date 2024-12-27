#include "createpost.h"
#include "../../../src/models/user/usermodel.h"
#include "../../home/home.h"

CreatePost::CreatePost(QWidget *parent)
    : QWidget{parent}
{

    mainContainer = new QVBoxLayout(this);
    titleArea = new QLineEdit();
    titleArea->setPlaceholderText("Enter Title");
    textArea = new QTextEdit();
    textArea->setPlaceholderText("Your Post Goes here");
    postBtn = new QPushButton("Post");

    mainContainer->addWidget(titleArea, 2);
    mainContainer->addWidget(textArea, 6);
    mainContainer->addWidget(postBtn, 2);

    connect(this->postBtn, &QPushButton::clicked, this, &CreatePost::on_postBtn_clicked);

    threadRepo = new ThreadRepository();
}
void CreatePost::on_postBtn_clicked()
{
    QString title = this->titleArea->text();
    QString text = this->textArea->toPlainText();

    UserModel *user = AuthenticatedUser::getInstance();
    int community_id = -1;;

    if(Home::getInstance()->centerArea->currentIndex() == 1){
        community_id = Home::getInstance()->communityPage->getCommunity().getId();
    }
    ThreadModel thread(0, title, text, 0, "", *user, community_id, -1);
    threadRepo->addThreadtoDb(thread);


}
