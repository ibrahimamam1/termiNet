#include "hashhelper.h"
#include <QCryptographicHash>

HashHelper::HashHelper(QObject *parent)
    : QObject{parent}
{}

QString HashHelper::hashString(const QString& target) {
    QByteArray byteArray = target.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);
    return hash.toHex();
}
