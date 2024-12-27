#ifndef SINGLEMESSAGE_H
#define SINGLEMESSAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include "../../../../src/models/message/messagemodel.h"

class SingleMessage : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainContainer;
    QLineEdit* messageText;
    int m_direction; // 1 = left , 2 = right
    MessageModel m_msg;
public:
    explicit SingleMessage(const MessageModel& msg ,int direction, QWidget *parent = nullptr);

signals:
};

#endif // SINGLEMESSAGE_H
