#ifndef COMMUNITYMODEL_H
#define COMMUNITYMODEL_H
#include <QImage>
#include "../category/category_model.h"
#include "../thread/threadmodel.h"

class CommunityModel
{
    size_t id;
    QString name;
    QString description;
    QImage iconImage;
    QImage bannerImage;
    QList<CategoryModel> categories;
    QList<ThreadModel> threads;
    QString created_at;
    size_t memberCount;

public:
    CommunityModel();
    CommunityModel(const QString& name, const QString& description,
                   const QImage& iconImage, const QImage& bannerImage,
                   const size_t id = 0, const QString& created_at = "",
                   const size_t member_count = 0);

    size_t getId() const;
    QString getName() const;
    QString getDescription() const;
    QImage getIconImage() const;
    QImage getBannerImage() const;
    QString getCreatedAt() const;
    size_t getMemberCount() const;
    QList<CategoryModel> getCategories() const;
    void setCategories(const QList<CategoryModel>& cats);
    QList<ThreadModel> getThreads() const;
};
#endif // COMMUNITYMODEL_H
