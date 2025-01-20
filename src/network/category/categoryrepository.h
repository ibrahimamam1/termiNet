#ifndef CATEGORY_REPOSITORY_H
#define CATEGORY_REPOSITORY_H
#include "../../models/category/category_model.h"

class CategoryRepository
{
public:
    CategoryRepository();
    static QList<CategoryModel> getCategories(const QString& filter, const QString& value);
    static QList<CategoryModel> getAllCategories();
    static QList<CategoryModel> getCategoriesForCommunity(size_t community_id);
};

#endif // CATEGORY_REPOSITORY_H
