#include "checkcomboboxlist.h"

CheckComboboxList::CheckComboboxList(QWidget *parent) :
    QWidget(parent)
{
    checkBox = new QCheckBox();    
    connect(checkBox, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));

    comboBox = new QComboBox();
    comboBox->setEnabled(false);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_combobox_indexChanged(int)));

    listWidget = new QListWidget();
    listWidget->setHidden(true);
    listWidget->setFixedHeight(55);
    listWidget->setSelectionMode(QAbstractItemView::NoSelection);

    QBoxLayout *cbLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    cbLayout->addWidget(checkBox, 1);
    cbLayout->addWidget(comboBox, 2);

    QBoxLayout *lwLayout = new QBoxLayout(QBoxLayout::Down);
    lwLayout->addWidget(listWidget);


    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Down);
    layout->addLayout(cbLayout);
    layout->addLayout(lwLayout);

    this->setLayout(layout);
}

void CheckComboboxList::init(TYPE type){
    this->switchInit(type);
}

void CheckComboboxList::switchInit(TYPE &type){
    switch(type) {
        case TAGS:
            checkBox->setText(AppResources::getTagStr());
            this->setComboBoxItemsTags();
            break;
    }
}

void CheckComboboxList::on_checkBox_clicked(){
    if(checkBox->isChecked()) {
        comboBox->setEnabled(true);
        listWidget->setHidden(false);
    }
    else if(!checkBox->isChecked()) {
        comboBox->setEnabled(false);
        listWidget->setHidden(true);
    }
    this->clear();
}

void CheckComboboxList::on_combobox_indexChanged(int index){
    if(!checkBox->isChecked())
        return;
    QString text = comboBox->itemText(index);
    int value = comboBox->itemData(index).toInt();
    for(int i(0); i < listWidget->count(); ++i) {
        if(listWidget->item(i)->text() == text)
            return;
    }
    this->addItem(text, value);
}

void CheckComboboxList::addItem(QString text, int value){
    MngrConnection::Instance().transaction();
    int userFindTagId = MngrQuerys::addUserFindTag(value);
    if(userFindTagId > 0) {
        MngrConnection::Instance().commit();
        listWidget->addItem(text);
    }
    else
        MngrConnection::Instance().rollback();
}

void CheckComboboxList::setComboBoxItemsTags(){
    MngrConnection::Instance().transaction();
    QMap<QString, int> tags = MngrQuerys::getTagsId();
    MngrConnection::Instance().commit();
    comboBox->clear();
    QMapIterator<QString, int> i(tags);
    while (i.hasNext()) {
        i.next();
        comboBox->addItem(i.key(), i.value());
    }
    comboBox->setCurrentIndex(-1);
}

void CheckComboboxList::clear(){
    MngrConnection::Instance().transaction();
    int result = MngrQuerys::deleteUserFindTags();
    if(result > 0){
        MngrConnection::Instance().commit();
        listWidget->clear();
    }
    else
        MngrConnection::Instance().rollback();
}

QVariant CheckComboboxList::getFlag(){
    QVariant value;
    if(comboBox->isEnabled() && listWidget->count() > 0)
       value = 1;
    return value;
}
