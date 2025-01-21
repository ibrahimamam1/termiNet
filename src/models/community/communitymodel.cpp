#include "communitymodel.h"
#include "../../network/community/communityrepository.h"
#include "../../network/threads/threadrepository.h"

CommunityModel::CommunityModel()
    : id(0),
    name(""),
    description(""),
    iconImage(""),
    bannerImage(""),
    categories()
{}

CommunityModel::CommunityModel(const QString& name, const QString& description,
                               const QImage& iconImage, const QImage& bannerImage,
                               const size_t id, const QString& created_at,
                               const size_t m_count)
    :name(name),
    description(description),
    iconImage(iconImage),
    bannerImage(bannerImage),
    id(id),
    created_at(created_at),
    memberCount(m_count)
{
    threads = ThreadRepository::loadAllThreadsFromCommunity(id);
}

size_t CommunityModel::getId() const {
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
void CommunityModel::setCategories(const QList<CategoryModel>& cats){
    categories = cats;
}
size_t CommunityModel::getMemberCount() const {
    return memberCount;
}

QList<ThreadModel> CommunityModel::getThreads() const{
    return threads;
}
