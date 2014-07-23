#include "viewlistwidget.h"

ViewListWidget::ViewListWidget(QWidget *parent, QListWidget *list) :
    QDialog(parent)
{
    lw = new QListWidget();
    lw->setFixedWidth(list->width() / 1.5);
    for(int i(0); i < list->count(); ++i){
        QListWidgetItem *item = list->item(i)->clone();
        lw->addItem(item);
    }

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(lw);

    this->setLayout(layout);
}

void ViewListWidget::scrollToBottom(){
    lw->scrollToBottom();
}
