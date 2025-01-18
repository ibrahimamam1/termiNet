#include "threadview.h"
#include "../thread/threadwidget.h"
#include "../../../src/network/threads/threadrepository.h"
#include <QScrollBar>

ThreadView::ThreadView(std::vector<ThreadModel>t_threads, QWidget *parent)
    : threads(t_threads), QWidget{parent}
{
    // Set up main layout
    mainContainer = new QHBoxLayout(this);
    setLayout(mainContainer);

    threadPages = new QStackedWidget(this);

    // Create scrollable area for threads with full space utilization
    scrollableAreaForThreads = new QScrollArea(this);
    scrollableAreaForThreads->setWidgetResizable(true);
    scrollableAreaForThreads->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollableAreaForThreads->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    commentPageLayout = new QSplitter(Qt::Vertical);

    scrollableAreaForComments = new QScrollArea(this);
    scrollableAreaForComments->setWidgetResizable(true);
    scrollableAreaForComments->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollableAreaForComments->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollableAreaForComments->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create threads container with vertical layout
    threadsContainer = new QWidget();
    threadsLayout = new QVBoxLayout(threadsContainer);

    commentsContainer = new QWidget();
    commentsLayout = new QVBoxLayout(commentsContainer);
    replyBox = new ReplyBox(this);

    // Populate threads
    for(const auto& thread : threads){
        ThreadWidget *threadWidget = new ThreadWidget(thread);
        connect(threadWidget, &ThreadWidget::commentIconClicked, this, [this, thread]() {
            switchToCommentScreen(thread);
        });

        threadsLayout->addWidget(threadWidget);
    }

    threadsLayout->addStretch(1);

    // Set the threads container as the widget for the scrollable area
    scrollableAreaForThreads->setWidget(threadsContainer);
    scrollableAreaForComments->setWidget(commentsContainer);

    commentPageLayout->addWidget(scrollableAreaForComments);
    commentPageLayout->addWidget(replyBox);
    commentPageLayout->setStretchFactor(0, 4);
    commentPageLayout->setStretchFactor(1, 0);

    // Add widgets to thread pages
    threadPages->addWidget(scrollableAreaForThreads);
    threadPages->addWidget(commentPageLayout);

    // Add thread pages to main container with proper stretching
    mainContainer->addWidget(threadPages, 8);
    mainContainer->addStretch(2);
}

// Destructor to clean up dynamically allocated widgets
ThreadView::~ThreadView() {

}

void ThreadView::switchToCommentScreen(const ThreadModel& thread) {
    // Clear existing comment widgets
    QLayoutItem* item;
    while ((item = commentsLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Load new comments for the specific thread
    comments = ThreadRepository::loadAllCommentsFromDb(thread.getThreadId());

    // Populate comments layout
    for(const auto& comment : comments){
        ThreadWidget *commentWidget = new ThreadWidget(comment);
        commentsLayout->addWidget(commentWidget);
    }

    commentsLayout->addStretch(1);

    // Switch to comments page
    replyBox->setCurrentThreadId(thread.getThreadId());
    threadPages->setCurrentIndex(1);
}
