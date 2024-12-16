#include "createmessage.h"
#include <QDebug>
#include <QSqlError>

CreateMessage::CreateMessage(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);

    searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Enter Username");
    connect(searchBar, &QLineEdit::returnPressed, this, &CreateMessage::onSearchReturnPressed);
    mainLayout->addWidget(searchBar);

    userStatusLabel = new QLabel();
    mainLayout->addWidget(userStatusLabel);

    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

void CreateMessage::onSearchReturnPressed()
{
    QString username = searchBar->text();
    if (!username.isEmpty()) {
        userStatusLabel->setText("Searching...");

        QSqlQuery q;
        q.prepare("Select * from users where user_name = :name");
        q.bindValue(":name", username);

        if(!q.exec()){
            qDebug() << "Failed to retreive user information" << q.lastError();
            return;
        }
        if(!q.next()){
            userStatusLabel->setText("User Not found");
            return;
        }
        receiver = UserModel(q.value(0).toInt(),q.value(1).toString(),q.value(2).toString(),q.value(3).toString(),q.value(4).toString(),q.value(5).toString(),q.value(7).toString());
        QString labelText = "<a href='#'>"+receiver.getName()+"</a>";
        userStatusLabel->setText(labelText);
        connect(userStatusLabel, &QLabel::linkActivated, this, &CreateMessage::onUserLinkClicked);
    }
}


void CreateMessage::onUserLinkClicked()
{
    emit userSelected(receiver);
}
