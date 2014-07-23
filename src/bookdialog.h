#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <objrecord.h>
#include <appresources.h>
#include <smartlineedit.h>
#include <listwidgetdialog.h>
#include <listwidgetdialogone.h>

#include <QMap>
#include <QLabel>
#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QDialogButtonBox>

class BookDialog : public QDialog
{
    Q_OBJECT

public:
    BookDialog(QWidget *parent = 0);
    void setRecord(ObjRecord &record);
    void updateRecord(ObjRecord &record);
    ObjRecord getRecord();
    QStringList getFileNames();  
    void setHiddenAddFilesButton(bool hidden);
    void setThemes(QStringList &arr);
    void setTags(QStringList &arr);
    void setName(QString name);
    ~BookDialog();

private:
    QLineEdit *lineEditName;
    QLineEdit *lineEditAuthor;
    QTextEdit *textEditDescription;
    SmartLineEdit *lineEditTheme;
    SmartLineEdit *lineEditTags;
    QPushButton *pushButtonAddFiles;
    QStringList fileNames;    

private slots:
    void on_pushButtonAddTheme_clicked();
    void on_pushButtonAddTags_clicked();
    void on_pushButtonAddFiles_clicked();
};

#endif // BOOKDIALOG_H
