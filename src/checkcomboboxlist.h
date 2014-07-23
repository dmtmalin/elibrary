#ifndef CHECKCOMBOBOXLIST_H
#define CHECKCOMBOBOXLIST_H

#include "mngrconnection.h"
#include "appresources.h"
#include "mngrquerys.h"

#include <QMap>
#include <QWidget>
#include <QVariant>
#include <QCheckBox>
#include <QComboBox>
#include <QBoxLayout>
#include <QListWidget>

class CheckComboboxList : public QWidget
{
    Q_OBJECT
public:
    explicit CheckComboboxList(QWidget *parent = 0);

public:
    enum TYPE { TAGS };
    void init(TYPE type);
    QVariant getFlag();

private:
    MngrConnection *mngrConnection;
    QListWidget *listWidget;
    QCheckBox *checkBox;
    QComboBox *comboBox;

    void addItem(QString text, int value);
    void setComboBoxItemsTags();    
    void switchInit(TYPE &type);
    void clear();

private slots:
    void on_checkBox_clicked();
    void on_combobox_indexChanged(int index);

};

#endif // CHECKCOMBOBOXLIST_H
