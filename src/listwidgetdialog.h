#ifndef LISTWIDGETDIALOG_H
#define LISTWIDGETDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QGridLayout>
#include <QDialogButtonBox>

class ListWidgetDialog : public QDialog
{
    Q_OBJECT

public:
    ListWidgetDialog(QWidget *parent = 0);
    void setWidgetItems(QStringList &arr);
    QString getValuesToString();

protected slots:
    void on_listWidgetLeft_doubleClicked(QListWidgetItem *item);
    void on_listWidgetRight_doubleClicked(QListWidgetItem *item);

private:
    QListWidget *listWidgetLeft;
    QListWidget *listWidgetRight;
};

#endif // LISTWIDGETDIALOG_H
