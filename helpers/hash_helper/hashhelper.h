#ifndef HASHHELPER_H
#define HASHHELPER_H

#include <QObject>

class HashHelper : public QObject
{
    Q_OBJECT
public:
    explicit HashHelper(QObject *parent = nullptr);
    static QString hashString(const QString& target);

signals:
};

#endif // HASHHELPER_H
