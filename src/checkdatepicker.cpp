#include "checkdatepicker.h"

CheckDatePicker::CheckDatePicker(QWidget *parent) :
    QWidget(parent)
{
    QDate date_curr = QDate::currentDate();

    calendar = new QCalendarWidget();
    calendar->setGridVisible(true);
    calendar->setMaximumDate(date_curr);
    connect(calendar, SIGNAL(selectionChanged()), this, SLOT(on_selection_changed()));

    checkBox = new QCheckBox();
    connect(checkBox, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));

    dateEdit = new QDateEdit();
    dateEdit->setMaximumDate(date_curr);
    dateEdit->setDate(date_curr);
    dateEdit->setEnabled(false);

    button = new QPushButton();
    button->setFixedSize(22, 22);
    button->setEnabled(false);
    button->setIcon(QIcon(":/png/Globe.png"));
    connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

    QBoxLayout *layout_dateBtn = new QBoxLayout(QBoxLayout::LeftToRight);
    layout_dateBtn->addWidget(dateEdit);
    layout_dateBtn->addWidget(button);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(checkBox, 1);
    layout->addLayout(layout_dateBtn, 2);

    this->setLayout(layout);
}

void CheckDatePicker::on_checkBox_clicked(){
    if(checkBox->isChecked()){
        dateEdit->setEnabled(true);
        button->setEnabled(true);
    }
    else if(!checkBox->isChecked()){
        dateEdit->setEnabled(false);
        button->setEnabled(false);
        calendar->close();
    }
}

void CheckDatePicker::on_button_clicked(){
    calendar->show();
}

void CheckDatePicker::on_selection_changed(){
    QDate date = calendar->selectedDate();
    dateEdit->setDate(date);
}

QVariant CheckDatePicker::getValue(){
    QVariant result;
    if(dateEdit->isEnabled()) {
        result = dateEdit->date().toString("dd.MM.yyyy");
    }
    return result;
}

void CheckDatePicker::setCheckBoxText(QString text){
    checkBox->setText(text);
}

void CheckDatePicker::closeCalendar(){
    calendar->close();
}
