#ifndef COMMUNITYMODEL_H
#define COMMUNITYMODEL_H
#include <QImage>
#include <vector>
#include "../categorymodel.h"
#include "../../src/models/thread/threadmodel.h"

class CommunityModel
{
    int id;
    QString name;
    QString description;
    QImage iconImage;
    QImage bannerImage;
    std::vector<CategoryModel> categories;
    std::vector<ThreadModel> threads;
public:
    CommunityModel();
    CommunityModel(int id, const QString& name, const QString& description, const QImage& iconImage, const QImage& bannerImage, const std::vector<CategoryModel>& categories, const QString& created_at = "");

    int getId() const;
    QString getName() const;
    QString getDescription() const;
    QImage getIconImage() const;
    QImage getBannerImage() const;
    int getMemberCount() const;
    std::vector<CategoryModel> getCategories() const;
    std::vector<ThreadModel> getThreads() const;
};
#endif // COMMUNITYMODEL_H
