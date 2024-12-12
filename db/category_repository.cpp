#include "category_repository.h"
#include<QSqlQuery>
#include<QSqlError>
#include "../models/categorymodel.h"

CategoryRepository::CategoryRepository() {}

QList<CategoryModel> CategoryRepository::getCategories(){
    QSqlQuery q;
    QList<CategoryModel> result;

    q.prepare("select * from categories;");

    if(!q.exec()){
        qDebug() << "failed to get categories";
    }
    while(q.next()){
        result.append(CategoryModel(q.value(0).toInt(), q.value(1).toString()));
    }
    return result;
}
CategoryModel CategoryRepository::getCategory(int id){
    QSqlQuery q;
    q.prepare("select * from categories where category_id = :id;");
    q.bindValue(":id", id);

    if(!q.exec()){
        qDebug() << "failed to get category";
    }
    if(q.next()){
        return CategoryModel(q.value(0).toInt(), q.value(1).toString());
    }
    return CategoryModel();
}

std::vector<CategoryModel> CategoryRepository::getCategoriesForCommunity(int community_id){
    std::vector<CategoryModel> categories;
    QSqlQuery q;
    q.prepare("select * from community_categories where community_id = :id;");
    q.bindValue(":id", community_id);

    if(!q.exec()){
        qDebug() << "failed to get categories : "<<q.lastError() ;
    }
    while(q.next()){
        CategoryModel cat = getCategory(q.value(1).toInt());
        categories.push_back(cat);
    }
    return categories;
}
