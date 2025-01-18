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

CommunityModel::CommunityModel(int id, const QString& name, const QString& description, const QImage& iconImage, const QImage& bannerImage, const std::vector<CategoryModel>& categories, const QString& created_at)
    : id(id),
    name(name),
    description(description),
    iconImage(iconImage),
    bannerImage(bannerImage),
    categories(categories)
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

std::vector<CategoryModel> CommunityModel::getCategories() const {
    return categories;
}

int CommunityModel::getMemberCount() const {
    return CommunityRepository::getMemberCount(id);
}

std::vector<ThreadModel> CommunityModel::getThreads() const{
    return threads;
}
