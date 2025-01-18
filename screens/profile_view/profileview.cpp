#include "profileview.h"
#include "../../src/models/user/authenticateduser.h"
#include "../../src/network/user/user_repository.h"
#include <QLabel>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

ProfileView::ProfileView(QWidget *parent)
    : QWidget(parent)
{
    // Set up the main layout
    setLayout(&mainLayout);

    // Profile Picture Section

    profileIcon = AuthenticatedUser::getInstance().getProfilePic();
    profilePic = new QLabel();
    profilePic->setPixmap(profileIcon.pixmap(QSize(100, 100)));

    changeProfilePic = new ClickableLabel(this);
    changeProfilePic->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Change Profile Picture</a>");
    changeProfilePic->setCursor(Qt::PointingHandCursor);
    changeProfilePic->setFixedSize(100, 100);
    connect(changeProfilePic, &ClickableLabel::clicked, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Choose Profile Picture"), "",
                                                        tr("Images (*.png *.jpg *.jpeg)"));
        if (!fileName.isEmpty()) {
            profileIcon = QIcon(fileName);
            profilePic->setPixmap(profileIcon.pixmap(QSize(100, 100)));
        }
    });

    // Username Row
    auto userNameRow = new QHBoxLayout();
    userName = new QLineEdit(this);
    userName->setText(AuthenticatedUser::getInstance().getName());
    userName->setReadOnly(true);
    changeUserName = new QPushButton("Edit", this);
    connect(changeUserName, &QPushButton::clicked, this, [this]() {
        userName->setReadOnly(!userName->isReadOnly());
        changeUserName->setText(userName->isReadOnly() ? "Edit" : "Done");
    });
    userNameRow->addWidget(userName);
    userNameRow->addWidget(changeUserName);

    // Email Row
    auto userEmailRow = new QHBoxLayout();
    userEmail = new QLineEdit(this);
    userEmail->setText(AuthenticatedUser::getInstance().getEmail());
    userEmail->setReadOnly(true);
    changeUserEmail = new QPushButton("Edit", this);
    connect(changeUserEmail, &QPushButton::clicked, this, [this]() {
        userEmail->setReadOnly(!userEmail->isReadOnly());
        changeUserEmail->setText(userEmail->isReadOnly() ? "Edit" : "Done");
    });
    userEmailRow->addWidget(userEmail);
    userEmailRow->addWidget(changeUserEmail);

    // Date of Birth Row
    auto userDobRow = new QHBoxLayout();
    userDob = new QLineEdit(this);
    userDob->setText(AuthenticatedUser::getInstance().getDob());
    userDob->setReadOnly(true);
    changeUserDob = new QPushButton("Edit", this);
    connect(changeUserDob, &QPushButton::clicked, this, [this]() {
        userDob->setReadOnly(!userDob->isReadOnly());
        changeUserDob->setText(userDob->isReadOnly() ? "Edit" : "Done");
    });
    userDobRow->addWidget(userDob);
    userDobRow->addWidget(changeUserDob);

    // Bio Row
    auto userBioRow = new QHBoxLayout();
    userBio = new QLineEdit(this);
    userBio->setPlaceholderText(AuthenticatedUser::getInstance().getBio());
    userBio->setReadOnly(true);
    changeUserBio = new QPushButton("Edit", this);
    connect(changeUserBio, &QPushButton::clicked, this, [this]() {
        userBio->setReadOnly(!userBio->isReadOnly());
        changeUserBio->setText(userBio->isReadOnly() ? "Edit" : "Done");
    });
    userBioRow->addWidget(userBio);
    userBioRow->addWidget(changeUserBio);

    // Save Button
    save = new QPushButton("Save Changes", this);
    save->setStyleSheet("QPushButton { padding: 8px; }");
    connect(save, &QPushButton::clicked, this, &ProfileView::onSaveButtonClicked);

    // Add all widgets to main layout
    mainLayout.addWidget(profilePic, 0, Qt::AlignHCenter);
    mainLayout.addWidget(changeProfilePic, 0, Qt::AlignHCenter);
    mainLayout.addLayout(userNameRow);
    mainLayout.addLayout(userEmailRow);
    mainLayout.addLayout(userDobRow);
    mainLayout.addLayout(userBioRow);
    mainLayout.addWidget(save);

    // Add some spacing for better appearance
    mainLayout.setSpacing(10);
    setMinimumWidth(400);
}

void ProfileView::onSaveButtonClicked() {
    auto instance = AuthenticatedUser::getInstance();

    // Update the username if it has changed
    if (instance.getName() != userName->text()) {
        qDebug() << "Updating User Name";
        UserRepository::updateUserName(userName->text());
    }

    // Update the email if it has changed
    if (instance.getEmail() != userEmail->text()) {
        qDebug() << "Updating User Email";
        UserRepository::updateUserEmail(userEmail->text());
    }

    // Update the date of birth if it has changed
    if (instance.getDob() != userDob->text()) {
        qDebug() << "Updating User Dob";
        UserRepository::updateUserDob(userDob->text());
    }

    // Update the bio if it has changed
    if (instance.getBio() != userBio->text()) {
        qDebug() << "Updating User Bio";
        UserRepository::updateUserBio(userBio->text());
    }

    // Update the profile picture if it has changed
    if (profileIcon.cacheKey() != instance.getProfilePic().cacheKey()) {
        qDebug() << "Updating User Profile Pic";
        UserRepository::updateUserProfilePic(profileIcon);
    }

    // Optionally, you can notify the user that changes have been saved
    QMessageBox::information(this, "Success", "Your changes have been saved!");
}
