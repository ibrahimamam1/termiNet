#ifndef THREADVIEW_H
#define THREADVIEW_H
#include <QWidget>
#include <QStackedWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <vector>
#include "../../../src/models/thread/threadmodel.h"
#include "../replyBox/replybox.h"

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
    std::vector<ThreadModel> threads;
    std::vector<ThreadModel> comments;

public:
    explicit ThreadView(std::vector<ThreadModel>t_threads, QWidget *parent = nullptr);
    void switchToCommentScreen(const ThreadModel& thread);
    ~ThreadView();  // Destructor to clean up dynamically allocated widgets

signals:
         // Add any signals you might need
};
#endif // THREADVIEW_H
