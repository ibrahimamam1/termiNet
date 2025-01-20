#include "category_selection_widget.h"
#include "../../../../network/category/categoryrepository.h"
#include "../category/category_widget.h"


CategorySelectionWidget::CategorySelectionWidget(QWidget* parent)
    :QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    categoriesLayout = new QGridLayout();
    headerText = new QLabel("Select Categories");

    allCategories = CategoryRepository::getAllCategories();
    //for every category create a category widget and add it to a grid layout
    for(auto category : allCategories){
        CategoryWidget *widget = new CategoryWidget(category.getName(), category.getId());
        categoriesLayout->addWidget(widget);
    }

    mainLayout->addWidget(headerText, 1);
    mainLayout->addLayout(categoriesLayout, 8);
    mainLayout->addStretch(1);

}

QList<CategoryModel> CategorySelectionWidget::getSelectedCategories() const{
    QList<CategoryModel> selectedCategories;

    // Iterate through all child widgets in the categoriesLayout
    for (int i = 0; i < categoriesLayout->count(); ++i) {
        QLayoutItem* item = categoriesLayout->itemAt(i);
        if (item) {
            CategoryWidget* categoryWidget = qobject_cast<CategoryWidget*>(item->widget());
            if (categoryWidget && categoryWidget->getIsSelected()) {
                CategoryModel cat(categoryWidget->getCategoryId(), categoryWidget->getCategoryName());
                selectedCategories.append(cat);
            }
        }
    }

    return selectedCategories;
}
