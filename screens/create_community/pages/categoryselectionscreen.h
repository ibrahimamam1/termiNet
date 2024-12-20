#ifndef CATEGORYSELECTIONSCREEN_H
#define CATEGORYSELECTIONSCREEN_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>

#include "../../../models/categorymodel.h"

class CategorySelectionScreen : public QWidget {
    Q_OBJECT
public:
    explicit CategorySelectionScreen(QWidget* parent = nullptr);

    // Method to get selected categories
    QList<CategoryModel> getCategories() const;
    std::vector<CategoryModel> getSelectedCategories() const;

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
