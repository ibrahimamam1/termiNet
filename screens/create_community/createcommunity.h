#ifndef CREATECOMMUNITY_H
#define CREATECOMMUNITY_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CreateCommunity : public QWidget
{
    Q_OBJECT
    QVBoxLayout *pageContainer;
    QStackedWidget *views;
    QWidget *page1;
    QWidget *page2;
    QWidget *page3;
    QHBoxLayout *bottombar;
    QPushButton *cancelBtn;
    QPushButton *prevBtn;
    QPushButton *nextBtn;

public:
    explicit CreateCommunity(QWidget *parent = nullptr);

signals:
};

#endif // CREATECOMMUNITY_H
