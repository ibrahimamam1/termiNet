#include "category_model.h"

CategoryModel::CategoryModel() : id(-1), name("") {}
CategoryModel::CategoryModel(const size_t& _id, const QString& _name) : id(_id), name(_name) {}
size_t CategoryModel::getId() const {return id;}
QString CategoryModel::getName() const {return name;}


