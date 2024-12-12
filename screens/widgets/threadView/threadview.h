#ifndef THREADVIEW_H
#define THREADVIEW_H

#include <QWidget>
#include <QStackedWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include "../../../models/thread/threadmodel.h"

class ThreadView : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    QStackedWidget *threadPages;

    QScrollArea *scrollableAreaForThreads;
    QWidget *threadsContainer;
    QVBoxLayout *threadsLayout;

    QScrollArea *scrollableAreaForComments;
    QWidget *commentsContainer;
    QVBoxLayout *commentsLayout;

    std::vector<ThreadModel> threads;

public:
    explicit ThreadView(std::vector<ThreadModel>t_threads , QWidget *parent = nullptr);

signals:
};

#endif // THREADVIEW_H
