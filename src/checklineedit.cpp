#include "checklineedit.h"

CheckLineEdit::CheckLineEdit(QWidget *parent) :
    QWidget(parent)
{
    checkBox = new QCheckBox();
    connect(checkBox, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));

    lineEdit = new QLineEdit();
    lineEdit->setEnabled(false);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(checkBox, 1);
    layout->addWidget(lineEdit, 2);

    this->setLayout(layout);
}

QVariant CheckLineEdit::getValue(){
    QVariant value;
    if(lineEdit->isEnabled())
       value = lineEdit->text();
    return value;
}

void CheckLineEdit::on_checkBox_clicked(){
    if(checkBox->isChecked())
        lineEdit->setEnabled(true);
    else if(!checkBox->isChecked())
        lineEdit->setEnabled(false);
}

void CheckLineEdit::setCheckBoxText(const QString str){
    checkBox->setText(str);
}
