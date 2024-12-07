#include "categorywidget.h"

CategoryWidget::CategoryWidget(const QString& categoryName, const int categoryId, const bool& isSelected, QWidget *parent)
    : m_categoryName(categoryName), m_categoryId(categoryId), m_isSelected(isSelected), QWidget{parent}
{
    m_baseColor = QColor(240, 240, 240);  // Light gray
    m_borderColor = QColor(200, 200, 200);  // Slightly darker gray for border
    m_selectedColor = QColor(52, 152, 219);  // Vibrant blue
    m_selectedTextColor = Qt::white;  // White text for contrast
    m_hoverColor = QColor(230, 230, 230);  // Very light gray
}
int CategoryWidget::getCategoryId() const{
    return m_categoryId;
}
QString CategoryWidget::getCategoryName() const{
    return m_categoryName;
}
bool CategoryWidget::getIsSelected() const {
    return m_isSelected;
}
void CategoryWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Choose color based on state
    QColor backgroundColor = m_isSelected ? m_selectedColor : m_baseColor;
    QColor textColor = m_isSelected ? m_selectedTextColor : Qt::black;

    // Draw circular background with slight border
    painter.setBrush(backgroundColor);
    painter.setPen(QPen(m_borderColor, 2));
    painter.drawEllipse(rect().adjusted(2, 2, -2, -2));

    // Draw category name
    painter.setPen(textColor);
    painter.drawText(rect(), Qt::AlignCenter, m_categoryName);
}

void CategoryWidget::mousePressEvent(QMouseEvent* event) {
    m_isSelected = !m_isSelected;
    update(); // Trigger repaint
    emit categoryToggled(m_categoryName, m_isSelected);
}
