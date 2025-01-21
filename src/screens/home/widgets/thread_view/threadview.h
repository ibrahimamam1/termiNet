#ifndef THREADVIEW_H
#define THREADVIEW_H
#include <QWidget>
#include <QStackedWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <vector>
#include "../../../../models/thread/threadmodel.h"
#include "widgets/replyBox/replybox.h"

class ThreadView : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *mainContainer;
    QStackedWidget *threadPages;
    QScrollArea *scrollableAreaForThreads;
    QWidget *threadsContainer;
    QVBoxLayout *threadsLayout;
    QWidget *commentPageContainer;
    QSplitter *commentPageLayout;
    QScrollArea *scrollableAreaForComments;
    QWidget *commentsContainer;
    QVBoxLayout *commentsLayout;
    ReplyBox *replyBox;
    QList<ThreadModel> threads;
    QList<ThreadModel> comments;

public:
    explicit ThreadView(const QList<ThreadModel>& t_threads, QWidget *parent = nullptr);
    void setThreads(const QList<ThreadModel>& t);
    void switchToCommentScreen(const ThreadModel& thread);
    void switchToHomeScreen();
    ~ThreadView();  // Destructor to clean up dynamically allocated widgets

signals:
         // Add any signals you might need
};
#endif // THREADVIEW_H
