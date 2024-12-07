#include "categorymodel.h"

CategoryModel::CategoryModel() : id(-1), name("") {}
CategoryModel::CategoryModel(const int _id, const QString _name) : id(_id), name(_name) {}
int CategoryModel::getId() const {return id;}
QString CategoryModel::getName() const {return name;}


