#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <appresources.h>
#include <smartlineedit.h>
#include <listwidgetdialog.h>
#include <listwidgetdialogone.h>

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
    QString getName();
    QString getAuthor();
    QString getTheme();
    QString getDescription();
    QStringList getTags();
    QStringList getFileNames();
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
    QStringList fileNames;

private slots:
    void on_pushButtonAddTheme_clicked();
    void on_pushButtonAddTags_clicked();
    void on_pushButtonAddFiles_clicked();
};

#endif // BOOKDIALOG_H
