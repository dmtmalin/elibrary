#include "checkcombobox.h"

CheckComboBox::CheckComboBox(QWidget *parent) :
    QWidget(parent)
{
    checkBox = new QCheckBox();
    connect(checkBox, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));

    comboBox = new QComboBox();
    comboBox->setEnabled(false);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(checkBox, 1);
    layout->addWidget(comboBox, 2);

    this->setLayout(layout);
}

void CheckComboBox::setCheckBoxText(const QString str){
    checkBox->setText(str);
}

void CheckComboBox::setComboBoxItems(const QMap<QString, int> &items){
    comboBox->clear();
    QMapIterator<QString, int> i(items);
    while (i.hasNext()) {
        i.next();
        comboBox->addItem(i.key(), i.value());
    }
}

void CheckComboBox::on_checkBox_clicked(){
    if(checkBox->isChecked())
        comboBox->setEnabled(true);
    else if(!checkBox->isChecked())
        comboBox->setEnabled(false);
}

QVariant CheckComboBox::getValue() {
    QVariant value;
    if(comboBox->isEnabled())
       value = comboBox->itemData(comboBox->currentIndex());
    return value;
}
