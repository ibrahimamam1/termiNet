#ifndef CATEGORYWIDGET_H
#define CATEGORYWIDGET_H

#include <QWidget>
#include <QPainter>

class CategoryWidget : public QWidget {
    Q_OBJECT
public:
    explicit CategoryWidget(const QString& categoryName, const bool& isSelected = false, QWidget* parent = nullptr);

    bool getIsSelected() const;
    QString getCategoryName() const;

signals:
    void categoryToggled(const QString& category, bool isSelected);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QString m_categoryName;
    bool m_isSelected;
    QColor m_baseColor;
    QColor m_selectedColor;
    QColor m_selectedTextColor;
    QColor m_hoverColor;
    QColor m_borderColor;
};

#endif // CATEGORYWIDGET_H
