#ifndef CHECKDATEPICKER_H
#define CHECKDATEPICKER_H

#include <QDate>
#include <QStyle>
#include <QWidget>
#include <QVariant>
#include <QDateEdit>
#include <QCheckBox>
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QCalendarWidget>

class CheckDatePicker : public QWidget
{
    Q_OBJECT
public:
    explicit CheckDatePicker(QWidget *parent = 0);
    void setCheckBoxText(QString text);
    void closeCalendar();
    QVariant getValue();

private:
    QCalendarWidget *calendar;
    QPushButton *button;
    QCheckBox *checkBox;
    QDateEdit *dateEdit;

private slots:
    void on_button_clicked();
    void on_checkBox_clicked();
    void on_selection_changed();

};

#endif // CHECKDATEPICKER_H
