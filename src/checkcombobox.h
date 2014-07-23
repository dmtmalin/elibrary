#ifndef CHECKCOMBOBOX_H
#define CHECKCOMBOBOX_H

#include <mngrconnection.h>
#include <mngrquerys.h>

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

public:
    enum TYPE { THEMES };
    void init(TYPE type);

    QCheckBox *checkBox;
    QComboBox *comboBox;
    QVariant getValue();  

private:
    void setComboBoxItemsThemes();
    void switchInit(TYPE &type);   

private slots:
    void on_checkBox_clicked();

};

#endif // CHECKCOMBOBOX_H
