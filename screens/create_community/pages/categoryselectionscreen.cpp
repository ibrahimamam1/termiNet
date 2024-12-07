#include "categoryselectionscreen.h"
#include "../../../db/category_repository.h"
#include "../widgets/categorywidget.h"


CategorySelectionScreen::CategorySelectionScreen(QWidget* parent)
    :QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    categoriesLayout = new QGridLayout();
    headerText = new QLabel("Select Categories");

    allCategories = getCategories();
    //for every category create a category widget and add it to a grid layout
    for(auto category : allCategories){
        CategoryWidget *widget = new CategoryWidget(category.getName(), category.getId());
        categoriesLayout->addWidget(widget);
    }

    mainLayout->addWidget(headerText, 1);
    mainLayout->addLayout(categoriesLayout, 8);
    mainLayout->addStretch(1);

}

QList<CategoryModel> CategorySelectionScreen::getCategories() const{
    return CategoryRepository::getCategories();
}

std::vector<CategoryModel> CategorySelectionScreen::getSelectedCategories() const{
    std::vector<CategoryModel> selectedCategories;

    // Iterate through all child widgets in the categoriesLayout
    for (int i = 0; i < categoriesLayout->count(); ++i) {
        QLayoutItem* item = categoriesLayout->itemAt(i);
        if (item) {
            CategoryWidget* categoryWidget = qobject_cast<CategoryWidget*>(item->widget());
            if (categoryWidget && categoryWidget->getIsSelected()) {
                CategoryModel cat(categoryWidget->getCategoryId(), categoryWidget->getCategoryName());
                selectedCategories.push_back(cat);
            }
        }
    }

    return selectedCategories;
}
