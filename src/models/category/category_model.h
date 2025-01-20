#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H
#include<QString>

class CategoryModel
{
public:
    CategoryModel();
    CategoryModel(const size_t& _id, const QString& _name);
    size_t getId() const;
    QString getName() const;



private:
    size_t id;
    QString name;
};

#endif // CATEGORYMODEL_H
