#include "createmessage.h"
#include "../../../../db/user/user_repository.h"
#include "../../messagepage.h"
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

        receiver = UserRepository::getUserFromName(username);
        QString labelText = "<a href='#'>"+receiver.getName()+"</a>";
        userStatusLabel->setText(labelText);
        connect(userStatusLabel, &QLabel::linkActivated, this, &CreateMessage::onUserLinkClicked);
    }
}


void CreateMessage::onUserLinkClicked()
{
    emit this->userSelected(receiver);
}

UserModel CreateMessage::getReceiver() const{ return receiver; }
