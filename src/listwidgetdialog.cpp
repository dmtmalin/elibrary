#include "listwidgetdialog.h"

ListWidgetDialog::ListWidgetDialog(QWidget *parent)
    :QDialog(parent)
{
    listWidgetLeft = new QListWidget();
    connect(listWidgetLeft, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_listWidgetLeft_doubleClicked(QListWidgetItem*)));
    listWidgetRight = new QListWidget();
    connect(listWidgetRight, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_listWidgetRight_doubleClicked(QListWidgetItem*)));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *pgrdLayout = new QGridLayout();
    pgrdLayout->addWidget(listWidgetLeft, 0, 0);
    pgrdLayout->addWidget(listWidgetRight, 0, 1);
    pgrdLayout->addWidget(buttonBox, 1, 1);

    this->setLayout(pgrdLayout);
}

void ListWidgetDialog::on_listWidgetLeft_doubleClicked(QListWidgetItem *item){
    if(item != NULL){
        int row = listWidgetLeft->currentRow();
        QListWidgetItem *new_item = listWidgetLeft->takeItem(row);
        listWidgetRight->addItem(new_item);
    }
}

void ListWidgetDialog::on_listWidgetRight_doubleClicked(QListWidgetItem *item){
    if(item != NULL){
        int row = listWidgetRight->currentRow();
        QListWidgetItem *new_item = listWidgetRight->takeItem(row);
        listWidgetLeft->addItem(new_item);
    }
}

void ListWidgetDialog::setWidgetItems(QStringList &arr){
    listWidgetLeft->addItems(arr);
}

QString ListWidgetDialog::getValuesToString() {
    QString text;
    for(int i(0); i < listWidgetRight->count(); ++i){
        QString str = listWidgetRight->item(i)->text() + ',';
        text += str;
    }
    text.remove(text.count() - 1, 1);
    return text;
}

