#ifndef COMUNITYDESCRIPTIONPAGE_H
#define COMUNITYDESCRIPTIONPAGE_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ComunityDescriptionWidget : public QWidget{
    Q_OBJECT
public:
    ComunityDescriptionWidget();
    QVBoxLayout *page1Layout;
    QLabel *headertext;
    QLineEdit *communityNameField;
    QTextEdit *communityDescription;

};

#endif // COMUNITYDESCRIPTIONPAGE_H
