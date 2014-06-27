#ifndef CHECKCOMBOBOX_H
#define CHECKCOMBOBOX_H

#include <QMap>
#include <QWidget>
#include <QVariant>
#include <QCheckBox>
#include <QComboBox>
#include <QBoxLayout>

class CheckComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit CheckComboBox(QWidget *parent = 0);
    void setCheckBoxText(const QString str);
    void setComboBoxItems(const QMap<QString, int> &items);
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QVariant getValue();

signals:

private slots:
    void on_checkBox_clicked();

};

#endif // CHECKCOMBOBOX_H
