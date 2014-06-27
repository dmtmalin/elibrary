#ifndef CHECKLINEEDIT_H
#define CHECKLINEEDIT_H

#include <QWidget>
#include <QVariant>
#include <QCheckBox>
#include <QLineEdit>
#include <QBoxLayout>

class CheckLineEdit : public QWidget
{
    Q_OBJECT
public:
    explicit CheckLineEdit(QWidget *parent = 0);
    void setCheckBoxText(const QString str);
    QVariant getValue();

private:
    QCheckBox *checkBox;
    QLineEdit *lineEdit;

private slots:
    void on_checkBox_clicked();

};

#endif // CHECKLINEEDIT_H
