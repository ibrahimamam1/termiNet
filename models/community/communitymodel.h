#ifndef COMMUNITYMODEL_H
#define COMMUNITYMODEL_H
#include <QImage>
#include <vector>
#include "../../src/models/category/category_model.h"
#include "../../src/models/thread/threadmodel.h"

class CommunityModel
{
    int id;
    QString name;
    QString description;
    QImage iconImage;
    QImage bannerImage;
    QList<CategoryModel> categories;
    std::vector<ThreadModel> threads;
    QString created_at;

public:
    CommunityModel();
    CommunityModel(const QString& name, const QString& description, const QImage& iconImage, const QImage& bannerImage, const QList<CategoryModel>& categories, const size_t id = 0, const QString& created_at = "");

    int getId() const;
    QString getName() const;
    QString getDescription() const;
    QImage getIconImage() const;
    QImage getBannerImage() const;
    QString getCreatedAt() const;
    int getMemberCount() const;
    QList<CategoryModel> getCategories() const;
    std::vector<ThreadModel> getThreads() const;
};
#endif // COMMUNITYMODEL_H
