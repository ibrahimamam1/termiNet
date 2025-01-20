#ifndef CATEGORYSELECTIONSCREEN_H
#define CATEGORYSELECTIONSCREEN_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>

#include "../../../../models/category/category_model.h"

class CategorySelectionWidget : public QWidget {
    Q_OBJECT
public:
    explicit CategorySelectionWidget(QWidget* parent = nullptr);

    // Method to get selected categories
    QList<CategoryModel> getSelectedCategories() const;

private:
    void setupCategoryLayout();
    void onCategoryToggled(const QString& category, bool isSelected);

    QSet<QString> selectedCategories;
    QList<CategoryModel>allCategories;
    QVBoxLayout* mainLayout;
    QGridLayout* categoriesLayout;
    QLabel *headerText;
};

#endif // CATEGORYSELECTIONSCREEN_H
