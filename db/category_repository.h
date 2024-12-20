#ifndef CATEGORY_REPOSITORY_H
#define CATEGORY_REPOSITORY_H
#include "../models/categorymodel.h"

class CategoryRepository
{
public:
    CategoryRepository();
    static QList<CategoryModel> getCategories();
    static std::vector<CategoryModel> getCategoriesForCommunity(int community_id);
    static CategoryModel getCategory(int id);
};

#endif // CATEGORY_REPOSITORY_H
