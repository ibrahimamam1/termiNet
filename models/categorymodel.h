#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H
#include<QString>

class CategoryModel
{
public:
    CategoryModel();
    CategoryModel(const int _id, const QString _name);
    int getId() const;
    QString getName() const;



private:
    int id;
    QString name;
};

#endif // CATEGORYMODEL_H
