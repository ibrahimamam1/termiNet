#include "searchview.h"
#include "../home/widgets/thread_view/widgets/thread/threadwidget.h"
#include "../../common/widgets/clickable_label.h"
#include "../home/home.h"

SearchView::SearchView(QWidget *parent) : QWidget(parent)
{
    tabs = new QTabWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabs);
    setLayout(layout);

    // Initialize tabs with empty widgets
    tabs->addTab(new QWidget(), "Threads");
    tabs->addTab(new QWidget(), "Communities");
    tabs->addTab(new QWidget(), "Users");
}
void SearchView::setSearchView(const QList<ThreadModel>& threads,
                               const QList<CommunityModel>& comms,
                               const QList<UserModel>& users)
{
    this->threads = threads;
    this->communities = comms;
    this->users = users;

    // Update each tab with the provided custom widget
    updateThreadsTab(this->threads);
    updateCommunitiesTab(this->communities);
    updateUsersTab(this->users);
}
void SearchView::updateThreadsTab(const QList<ThreadModel>& threads)
{
    QWidget *threadTab = tabs->widget(0); // Get the Threads tab
    QLayout *layout = threadTab->layout();

    // Clear existing content
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    // Create a new layout for the tab
    QVBoxLayout *newLayout = new QVBoxLayout(threadTab);
    threadTab->setLayout(newLayout);

    // Add custom widgets for each thread
    for (const auto& thread : threads) {
        // Create your custom ThreadWidget here
        ThreadWidget *threadWidget = new ThreadWidget(thread, threadTab);
        QVBoxLayout *widgetLayout = new QVBoxLayout(threadWidget);
        threadWidget->setLayout(widgetLayout);

        newLayout->addWidget(threadWidget);
    }

    // Add a stretch to push all content to the top
    newLayout->addStretch();
}

void SearchView::updateCommunitiesTab(const QList<CommunityModel>& communities)
{
    Home& home = Home::getInstance();
    QWidget *communityTab = tabs->widget(1); // Get the Communities tab
    QLayout *layout = communityTab->layout();

    // Clear existing content
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    // Create a new layout for the tab
    QVBoxLayout *newLayout = new QVBoxLayout(communityTab);
    communityTab->setLayout(newLayout);

    // Add custom widgets for each community
    for (const auto& community : communities) {
        // Create your custom CommunityWidget here
        ClickableLabel *communityWidget = new ClickableLabel(communityTab);
        QString label = "<a href='#'>" + community.getName() + "</a>";
        communityWidget->setText(label);
        communityWidget->setTextInteractionFlags(Qt::TextBrowserInteraction);
        QObject::connect(communityWidget, &ClickableLabel::clicked, this,[&]{
            home.communityPage->setCommunityPage(community);
            home.communityPage->update();
            home.centerArea->setCurrentIndex(1);
        });
        QVBoxLayout *widgetLayout = new QVBoxLayout(communityWidget);
        communityWidget->setLayout(widgetLayout);

        newLayout->addWidget(communityWidget);
    }

    // Add a stretch to push all content to the top
    newLayout->addStretch();
}

void SearchView::updateUsersTab(const QList<UserModel>& users)
{
    QWidget *userTab = tabs->widget(2); // Get the Users tab
    QLayout *layout = userTab->layout();

    // Clear existing content
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout;
    }

    // Create a new layout for the tab
    QVBoxLayout *newLayout = new QVBoxLayout(userTab);
    userTab->setLayout(newLayout);

    // Add custom widgets for each user
    for (const auto& user : users) {
        // Create your custom UserWidget here
        ClickableLabel *userWidget = new ClickableLabel(userTab);
        QString label = "<a href='#'>" + user.getName() + "</a>";
        userWidget->setText(label);
        userWidget->setTextInteractionFlags(Qt::TextBrowserInteraction);
        QObject::connect(userWidget, &ClickableLabel::clicked, this,[&]{
            qDebug() << "Switch to profile screen for user: " << user.getName();
        });
        QVBoxLayout *widgetLayout = new QVBoxLayout(userWidget);
        userWidget->setLayout(widgetLayout);

        newLayout->addWidget(userWidget);
    }

    // Add a stretch to push all content to the top
    newLayout->addStretch();
}
