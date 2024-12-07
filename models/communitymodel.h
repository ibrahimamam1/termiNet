#ifndef COMMUNITYMODEL_H
#define COMMUNITYMODEL_H
#include <vector>
#include "categorymodel.h"

class CommunityModel
{
    int id;
    QString name;
    QString description;
    QString iconImage;
    QString bannerImage;
    std::vector<CategoryModel> categories;
public:
    CommunityModel();
    CommunityModel(int id, const QString& name, const QString& description, const QString& iconImage, const QString& bannerImage, const std::vector<CategoryModel>& categories);

    int getId() const;
    QString getName() const;
    QString getDescription() const;
    QString getIconImage() const;
    QString getBannerImage() const;
    std::vector<CategoryModel> getCategories() const;
};
#endif // COMMUNITYMODEL_H
