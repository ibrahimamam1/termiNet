#include "category_repository.h"
#include<QSqlQuery>
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
static CategoryModel getCategory(int id){
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
