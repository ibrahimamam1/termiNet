#include "community_description_widget.h"


ComunityDescriptionWidget::ComunityDescriptionWidget() {

    page1Layout = new QVBoxLayout(this);
    headertext = new QLabel();
    headertext->setText("Create Your Own Amazing Communities");
    communityNameField = new QLineEdit();
    communityNameField->setPlaceholderText("Community Name *");
    communityDescription = new QTextEdit();
    communityDescription->setPlaceholderText("Description *");

    page1Layout->addWidget(headertext, 1);
    page1Layout->addWidget(communityNameField, 1);
    page1Layout->addWidget(communityDescription, 2);
    page1Layout->addStretch(1);
}
