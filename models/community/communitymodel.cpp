#include "communitymodel.h"
#include "../../db/communityrepository.h"
#include "../../src/network/threads/threadrepository.h"

CommunityModel::CommunityModel()
    : id(-1),
    name(""),
    description(""),
    iconImage(""),
    bannerImage(""),
    categories()
{}

CommunityModel::CommunityModel(const QString& name, const QString& description, const QImage& iconImage, const QImage& bannerImage, const QList<CategoryModel>& categories, const size_t id,const QString& created_at)
    :name(name),
    description(description),
    iconImage(iconImage),
    bannerImage(bannerImage),
    categories(categories),
    id(id),
    created_at(created_at)
{
    threads = ThreadRepository::loadAllThreadsFromCommunity(id);
}

int CommunityModel::getId() const {
    return id;
}

QString CommunityModel::getName() const {
    return name;
}

QString CommunityModel::getDescription() const {
    return description;
}

QImage CommunityModel::getIconImage() const {
    return iconImage;
}

QImage CommunityModel::getBannerImage() const {
    return bannerImage;
}

QString CommunityModel::getCreatedAt() const {
    return created_at;
}
QList<CategoryModel> CommunityModel::getCategories() const {
    return categories;
}

int CommunityModel::getMemberCount() const {
    return CommunityRepository::getMemberCount(id);
}

std::vector<ThreadModel> CommunityModel::getThreads() const{
    return threads;
}
