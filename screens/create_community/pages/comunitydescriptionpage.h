#ifndef COMUNITYDESCRIPTIONPAGE_H
#define COMUNITYDESCRIPTIONPAGE_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ComunityDescriptionPage : public QWidget{
    Q_OBJECT
public:
    ComunityDescriptionPage();
    QVBoxLayout *page1Layout;
    QLabel *headertext;
    QLineEdit *communityNameField;
    QTextEdit *communityDescription;

};

#endif // COMUNITYDESCRIPTIONPAGE_H
