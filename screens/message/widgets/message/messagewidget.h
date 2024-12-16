#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "../../../../models/message/messagemodel.h"

class MessageWidget : public QWidget
{
    QVBoxLayout *mainLayout;
    QLabel *userName;
    QLineEdit *preview;
public:
    MessageWidget(const MessageModel& msg, QWidget *parent = nullptr);
};

#endif // MESSAGEWIDGET_H
