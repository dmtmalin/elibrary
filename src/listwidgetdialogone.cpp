#include "listwidgetdialogone.h"

ListWidgetDialogOne::ListWidgetDialogOne(QWidget *parent)
    : QDialog(parent)
{
    listWidget = new QListWidget();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *pgrdLayout = new QGridLayout();
    pgrdLayout->addWidget(listWidget, 0, 0);
    pgrdLayout->addWidget(buttonBox, 1, 0);

    this->setLayout(pgrdLayout);
}

void ListWidgetDialogOne::setWidgetItems(QStringList &arr){
    listWidget->addItems(arr);
}

QString ListWidgetDialogOne::getValueToString() {
    QString str = "";
    if(listWidget->selectedItems().count() == 1)
        str = listWidget->item(listWidget->currentRow())->text();
    return str;
}
