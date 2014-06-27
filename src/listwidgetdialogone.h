#ifndef LISTWIDGETDIALOGONE_H
#define LISTWIDGETDIALOGONE_H

#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QDialogButtonBox>

class ListWidgetDialogOne : public QDialog
{
    Q_OBJECT

public:
    ListWidgetDialogOne(QWidget *parent = 0);
    void setWidgetItems(QStringList &arr);
    QString getValueToString();

private:
    QListWidget *listWidget;
};

#endif // LISTWIDGETDIALOGONE_H
