#include "login.h"
#include "signup.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
{
    mainContainer = new QHBoxLayout(this);
    loginContainer = new QVBoxLayout();
    formContainer = new QVBoxLayout();  // Removed parent to avoid multiple parents
    logo = new QLabel(this);
    welcomeText = new QLabel(this);
    emailField = new QLineEdit(this);
    passwordField = new QLineEdit(this);
    loginBtn = new QPushButton(this);
    forgotPassword = new QLabel(this);
    createAccount = new QLabel(this);
    divider = new QHBoxLayout();  // Removed parent
    socials = new QHBoxLayout();  // Fixed typo from 'social' to 'socials'

    //setup Fonts
    QFont welcomeFont = welcomeText->font();
    welcomeFont.setPointSize(22);
    welcomeFont.setBold(true);

    // Set basic properties of elements
    logo->setPixmap(QPixmap("../assets/logo.png"));
    welcomeText->setText("Welcome Back!");
    welcomeText->setFont(welcomeFont);
    emailField->setPlaceholderText("Enter Your Email");
    passwordField->setPlaceholderText("Enter Password");
    passwordField->setEchoMode(QLineEdit::Password);
    loginBtn->setText("Login");

    // Connect login button to slot
    connect(loginBtn, &QPushButton::clicked, this, &Login::on_login_btn_clicked);

    // Style forgot password label
    forgotPassword->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Forgot Password?</a>");
    forgotPassword->setTextFormat(Qt::RichText);
    forgotPassword->setTextInteractionFlags(Qt::TextBrowserInteraction);

    // Style create account label
    createAccount->setText("<a href='#' style='color: #007bff; text-decoration: underline;'>Create an Account</a>");
    createAccount->setTextFormat(Qt::RichText);
    createAccount->setTextInteractionFlags(Qt::TextBrowserInteraction);

    // Add form items to formContainer
    formContainer->addWidget(emailField, 2);
    formContainer->addWidget(passwordField, 2);
    formContainer->addWidget(loginBtn, 1);

    // Add divider items
    QFrame* leftLine = new QFrame(this);
    leftLine->setFrameShape(QFrame::HLine);
    leftLine->setFrameShadow(QFrame::Sunken);

    QFrame* rightLine = new QFrame(this);
    rightLine->setFrameShape(QFrame::HLine);
    rightLine->setFrameShadow(QFrame::Sunken);

    QLabel* orLabel = new QLabel("OR", this);
    orLabel->setAlignment(Qt::AlignCenter);

    divider->addWidget(leftLine, 4);
    divider->addWidget(orLabel, 2);
    divider->addWidget(rightLine, 4);

    // Add social items
    socials->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    QLabel* googleLogo = new QLabel(this);
    QLabel* facebookLogo = new QLabel(this);
    googleLogo->setPixmap(QPixmap("../assets/google.png"));
    facebookLogo->setPixmap(QPixmap("../assets/facebook.png"));
    socials->addWidget(googleLogo, 1);
    socials->addWidget(facebookLogo, 1);
    socials->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Set login container to take full space
    this->setLayout(loginContainer);

    // Add elements to loginContainer
    loginContainer->addWidget(logo, 1);
    loginContainer->addWidget(welcomeText, 1, Qt::AlignCenter);
    loginContainer->addLayout(formContainer, 4);
    loginContainer->addWidget(forgotPassword, 1);
    loginContainer->addWidget(createAccount, 1);
    loginContainer->addLayout(divider, 1);
    loginContainer->addLayout(socials, 1);

    //add login container and make sure it is alaways in the center
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
    std::string email = emailField->text().toStdString();
    std::string pass = passwordField->text().toStdString();
    bool login = false;

    qDebug() << "email: "<< email << " pass: "<< pass;

    QSqlQuery q;
    q.prepare("SELECT login_check(:email, :password)");

    q.bindValue(":email", QString::fromStdString(email));
    q.bindValue(":password", QString::fromStdString(pass));

    // Execute the query
    if (!q.exec()) {
        qDebug() << "Error executing login_check:" << q.lastError().text();
        return ;
    }

    // Retrieve and check the result
    if (q.next()) {
        login = q.value(0).toBool();
    } else {
        qDebug() << "No result returned from login_check function.";
    }

    if(login){

        UserModel *user = UserModel::getInstance();

        //get all user data and convert to user model
        q.prepare("SELECT * FROM users WHERE user_email=:email");
        q.bindValue(":email", QString::fromStdString(email));

        if(!q.exec()){
            qDebug() << "Failed to get Login Data\n";
            return ;
        }

        if(q.next()){
            user->setId(q.value(0).toInt());
            user->setName(q.value(1).toString().toStdString());
            user->setEmail(q.value(2).toString().toStdString());
            user->setSex(q.value(3).toString().toStdString());
            user->setDob(q.value(4).toString().toStdString());
            user->setBio(q.value(5).toString().toStdString());
            user->setCreatedAt(q.value(7).toString().toStdString());

            //debug test
            // qDebug()<<"Id : "<<user->getId();
            // qDebug()<<"Name : "<<user->getName();
            // qDebug()<<"Email : "<<user->getEmail();
            // qDebug()<<"DOB : "<<user->getDob();
            // qDebug()<<"Bio : "<<user->getBio();
            // qDebug()<<"Created At : "<<user->getCreatedAt();

            //Go to next screen here
            emit loginSuccessful();
        }

    }
    else{
        qDebug() << "Login Failed";
    }
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
    signupPage->show();
    this->close();
}

