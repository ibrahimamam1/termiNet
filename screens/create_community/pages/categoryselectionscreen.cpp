#include "categoryselectionscreen.h"
#include "../../../db/category_repository.h"
#include "../widgets/categorywidget.h"


CategorySelectionScreen::CategorySelectionScreen(QWidget* parent)
    :QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    categoriesLayout = new QGridLayout();
    headerText = new QLabel("Select Categories");

    QList<CategoryModel>allCategories;
    allCategories = getSelectedCategories();
    //for every category create a category widget and add it to a grid layout
    for(auto category : allCategories){
        CategoryWidget *widget = new CategoryWidget(category.getName());
        categoriesLayout->addWidget(widget);
    }

    mainLayout->addWidget(headerText, 1);
    mainLayout->addLayout(categoriesLayout, 8);
    mainLayout->addStretch(1);

}

QList<CategoryModel> CategorySelectionScreen::getSelectedCategories() const{
    return CategoryRepository::getCategories();
}
