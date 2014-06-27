#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <fileutils.h>
#include <mngrquerys.h>
#include <bookdialog.h>
#include <appresources.h>
#include <checkcombobox.h>
#include <checklineedit.h>
#include <mngrconnection.h>

#include <QMap>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QThread>
#include <QWidget>
#include <QMenuBar>
#include <QGroupBox>
#include <QShortcut>
#include <QTableView>
#include <QBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QtConcurrent/QtConcurrentRun>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    MngrConnection mngrConnection;    
    QSqlQueryModel *mdlRecords;
    QSqlQueryModel *mdlFiles;
    CheckComboBox *cbThemes;
    CheckComboBox *cbTags;
    CheckLineEdit *leAuthor;
    CheckLineEdit *leName;
    QTableView *tableViewRecord;
    QTableView *tableViewFile;
    QLabel *lTags;
    QString tempPath;

    void addBook(QStringList fileNames, QStringList themes, QStringList tags);
    void addBookReport(QString name, QString author, QString theme);
    void initCheckComboBoxs();

protected slots:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void new_record();
    void selection_changed(const QItemSelection &selected);
    void open_record(QModelIndex index);
    void open_record();
    void open_file(QModelIndex index);
    void open_file();
    void on_pushButtonFind_clicked();   
};

#endif // MAINWIDGET_H
