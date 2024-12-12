#include "threadview.h"
#include "../thread/threadwidget.h"


ThreadView::ThreadView(std::vector<ThreadModel>t_threads , QWidget *parent)
    : threads(t_threads), QWidget{parent}
{
    mainContainer = new QHBoxLayout();
    threadPages = new QStackedWidget(this);

    scrollableAreaForThreads = new QScrollArea();
    scrollableAreaForThreads->setWidgetResizable(true);
    threadsContainer = new QWidget();
    threadsLayout = new QVBoxLayout();


    commentsContainer = new QWidget();
    commentsLayout = new QVBoxLayout();

    //set up the threads
    for(auto thread : threads){
        ThreadWidget *threadWidget = new ThreadWidget(thread);
        threadsLayout->addWidget(threadWidget);
    }
    threadsContainer->setLayout(threadsLayout);

    threadPages->addWidget(threadsContainer);
    threadPages->addWidget(commentsContainer);

    mainContainer->addWidget(threadPages, 8);
    mainContainer->addStretch(2);
}
