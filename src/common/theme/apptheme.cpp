#include "apptheme.h"
#include <QPalette>
#include <QColor>

AppTheme::AppTheme(QObject *parent) {}
QPalette AppTheme::getDarkPalette(){
        QPalette darkPalette;

        // Terminal-style colors
        QColor backgroundColor(12, 12, 12);      // Very dark gray, almost black
        QColor textColor(0, 255, 0);            // Classic terminal green
        QColor selectionColor(0, 128, 0);       // Darker green for selections
        QColor disabledColor(128, 128, 128);    // Gray for disabled elements

        // Set colors for various palette elements
        darkPalette.setColor(QPalette::Window, backgroundColor);
        darkPalette.setColor(QPalette::WindowText, textColor);
        darkPalette.setColor(QPalette::Base, QColor(0, 0, 0));
        darkPalette.setColor(QPalette::AlternateBase, backgroundColor);
        darkPalette.setColor(QPalette::PlaceholderText, QColor(0, 200, 0));
        darkPalette.setColor(QPalette::Text, textColor);
        darkPalette.setColor(QPalette::Button, backgroundColor);
        darkPalette.setColor(QPalette::ButtonText, textColor);
        darkPalette.setColor(QPalette::Link, QColor(0, 255, 128));
        darkPalette.setColor(QPalette::LinkVisited, QColor(0, 200, 100));

        // Highlight colors
        darkPalette.setColor(QPalette::Highlight, selectionColor);
        darkPalette.setColor(QPalette::HighlightedText, Qt::white);

        // Disabled colors
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
        darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, disabledColor);

        return darkPalette;
    }
QPalette AppTheme::getLightPalette() {
    return QPalette();
}
