#include "createpost.h"
#include "../../../../models/user/usermodel.h"
#include "../../../../models/user/authenticateduser.h"
#include "../../home.h"
#include <QTimer>

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

    connect(this->postBtn, &QPushButton::clicked, this, &CreatePost::onPostBtnClicked);

}
void CreatePost::onPostBtnClicked()
{
    QString title = this->titleArea->text();
    QString text = this->textArea->toPlainText();

    UserModel& user = AuthenticatedUser::getInstance();
    int communityId = 0;
    if(Home::getInstance().centerArea->currentIndex() == 1){
        communityId = Home::getInstance().communityPage->getCommunity().getId();
    }
    ThreadModel thread(title, text, user, communityId);
    bool success = ThreadRepository::postNewThread(thread);
    if(success){
        title.clear();
        text.clear();
        this->hide();
    }
    emit postCreated(success);



}
