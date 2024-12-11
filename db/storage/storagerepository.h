#ifndef STORAGEREPOSITORY_H
#define STORAGEREPOSITORY_H
#include <QImage>

class StorageRepository
{
public:
    StorageRepository();
    static QImage getIconImage(QString& ref);
    static QImage getBannerImage(QString& ref);
};

#endif // STORAGEREPOSITORY_H
