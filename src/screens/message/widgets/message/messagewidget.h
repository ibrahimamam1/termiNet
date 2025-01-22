#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "../../../../src/models/message/messagemodel.h"

class MessageWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *mainLayout;
    QLabel *userName;
    QLineEdit *preview;
    MessageModel message;

public:
    MessageWidget(const MessageModel& msg, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void conversationClicked(const UserModel& otherUser);
};

#endif // MESSAGEWIDGET_H
