#include "login.h"
#include "signup.h"
#include "../helpers/api_client/apiclient.h"
#include "../helpers/hash_helper/hashhelper.h"
#include <QJsonDocument>
#include <QJsonObject>

Login::Login(QWidget *parent)
    : QDialog(parent)
{
    mainContainer = new QHBoxLayout(this);
    loginContainer = new QVBoxLayout();
    formContainer = new QVBoxLayout();
    bottomContainer = new QVBoxLayout();
    logo = new QLabel(this);
    welcomeText = new QLabel(this);
    emailField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    loginBtn = new QPushButton(this);
    forgotPassword = new QLabel(this);
    createAccount = new QLabel(this);
    divider = new DividerWidget(this);
    socials = new SocialsWidget(this);  // Fixed typo from 'social' to 'socials'

    //setup Fonts
    QFont welcomeFont = welcomeText->font();
    welcomeFont.setPointSize(22);
    welcomeFont.setBold(true);

    // Setup Logo
    logo->setPixmap(QPixmap("../assets/logo.png"));

    //setup Welcome Text
    welcomeText->setText("Welcome Back!");
    welcomeText->setFont(welcomeFont);

    //setUp Form field with email and password
    emailField->setPlaceholderText("Enter Your Email");
    passwordField->setPlaceholderText("Enter Password");
    passwordField->setEchoMode(QLineEdit::Password);
    loginBtn->setText("Login");
    formContainer->addWidget(emailField, 2);
    formContainer->addWidget(passwordField, 2);
    formContainer->addWidget(loginBtn, 1);
    connect(loginBtn, &QPushButton::clicked, this, &Login::on_login_btn_clicked); // Connect login button to slot

    // SetUp forgot password label
    forgotPassword->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Forgot Password?</a>");
    forgotPassword->setTextFormat(Qt::RichText);
    forgotPassword->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(forgotPassword, &QLabel::linkActivated, this, &Login::onForgotPasswordClicked); //link to forgot password handler

    // SetUp create account label
    createAccount->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Create an Account</a>");
    createAccount->setTextFormat(Qt::RichText);
    createAccount->setTextInteractionFlags(Qt::TextBrowserInteraction);
    connect(createAccount, &QLabel::linkActivated, this, &Login::onCreateAccountClicked); //link to on click event handler

    //setup bottom Container
    bottomContainer->addWidget(forgotPassword, 1);
    bottomContainer->addWidget(createAccount, 1);
    bottomContainer->addStretch(2);

    // Setup Logincontainer
    this->setLayout(loginContainer); //ensures login container takes all available space
    loginContainer->addWidget(logo, 1);
    loginContainer->addWidget(welcomeText, 1, Qt::AlignCenter);
    loginContainer->addLayout(formContainer, 4);
    loginContainer->addLayout(bottomContainer, 1);
    loginContainer->addWidget(divider, 1);
    loginContainer->addWidget(socials, 1);
    loginContainer->addStretch(2);

    //Centralise Login Container so that is always is in the center of the window
    mainContainer->addStretch(4);
    mainContainer->addLayout(loginContainer,2);
    mainContainer->addStretch(4);

    // Set minimum size for the dialog
    this->setMinimumSize(400, 600);
}

Login::~Login()
{

    delete logo;
    delete welcomeText;
    delete emailField;
    delete passwordField;
    delete loginBtn;
    delete forgotPassword;
    delete createAccount;
    delete divider;
    delete socials;
    delete formContainer;
    delete loginContainer;
    delete mainContainer;
}
void Login::on_login_btn_clicked()
{
    QString email = emailField->text();
    QString pass = HashHelper::hashString(passwordField->text());
    ApiClient *apiclient = ApiClient::getInstance();

    // First request - Login
    QString loginUri = apiclient->getLoginUrl() + email + "/" + pass;
    QNetworkReply *loginReply = apiclient->makeGetRequest(loginUri);

    QPointer<QNetworkReply> safeLoginReply(loginReply);

    // Connect login request
    connect(loginReply, &QNetworkReply::finished, this, [this, email, safeLoginReply]() {
        if (!safeLoginReply) {
            return;
        }

        bool loginSuccessful = false;

        if (safeLoginReply->error() == QNetworkReply::NoError) {
            QByteArray data = safeLoginReply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject jsonObject = jsonDoc.object();
                if (jsonObject.contains("body")) {
                    QJsonObject body = jsonObject["body"].toObject();
                    loginSuccessful = body["Grant Access"].toBool();
                }
            } else {
                qDebug() << "Invalid response format, not a json object";
            }
        } else {
            qDebug() << "Login Error:" << safeLoginReply->errorString();
        }

        safeLoginReply->deleteLater();

        if (loginSuccessful) {
            // Second request - Get User Data
            QString userUri = ApiClient::getInstance()->getUserDataUrl() + email;
            QNetworkReply *userDataReply = ApiClient::getInstance()->makeGetRequest(userUri);
            QPointer<QNetworkReply> safeUserDataReply(userDataReply);

            connect(userDataReply, &QNetworkReply::finished, this, [this, safeUserDataReply]() {
                if (!safeUserDataReply) {
                    return;
                }

                if (safeUserDataReply->error() == QNetworkReply::NoError) {
                    qDebug() << "No Error whatsoever";
                    QByteArray data = safeUserDataReply->readAll();
                    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

                    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                        qDebug() << "Response is not null";
                        QJsonObject jsonObject = jsonDoc.object();
                        if (jsonObject.contains("body")) {
                            qDebug() << "Yup found body";
                            QJsonObject body = jsonObject["body"].toObject();

                            UserModel *user = new UserModel();
                            user->setId(body["user_id"].toInt());
                            user->setName(body["user_name"].toString());
                            user->setEmail(body["user_email"].toString());
                            user->setSex(body["user_sex"].toString());
                            user->setDob(body["user_dob"].toString());
                            user->setCreatedAt(body["created_at"].toString());

                            AuthenticatedUser::setInstance(*user);
                            emit this->loginSuccessful();

                            delete user; // Clean up if not using setInstance
                        }
                    } else {
                        qDebug() << "Invalid response format, not a json object";
                    }
                } else {
                    qDebug() << "User Data Error:" << safeUserDataReply->errorString();
                }

                safeUserDataReply->deleteLater();
            });

        } else {
            QMessageBox loginFailedBox;
            loginFailedBox.setIcon(QMessageBox::Critical);
            loginFailedBox.setWindowTitle("Login Failed");
            loginFailedBox.setText("Login Failed");
            loginFailedBox.setInformativeText(QString("Incorrect user name or password. Please try again"));
            loginFailedBox.exec();
        }
    });
}
void Login::onForgotPasswordClicked()
{
    // Handle forgot password click
    qDebug() << "Forgot password clicked";
    // Add your logic here - maybe open a new dialog or navigate to reset password page
}

void Login::onCreateAccountClicked()
{
    //Switch To create Account Page
    auto signupPage = new Signup();
    signupPage->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    signupPage->show();
    // Connect login success signal
    QObject::connect(signupPage, &Signup::signupSuccessful, [this, signupPage]() {
        emit loginSuccessful();
    });

}

