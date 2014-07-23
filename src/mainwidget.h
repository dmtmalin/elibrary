#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <objfile.h>
#include <watcher.h>
#include <mytracer.h>
#include <fileutils.h>
#include <objrecord.h>
#include <mngrquerys.h>
#include <bookdialog.h>
#include <appsettings.h>
#include <appresources.h>
#include <checkcombobox.h>
#include <checklineedit.h>
#include <mngrconnection.h>
#include <viewlistwidget.h>
#include <checkdatepicker.h>
#include <checkcomboboxlist.h>
#include <convertwkhtmltopdf.h>

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
#include <QPushButton>
#include <QMessageBox>
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
    QSqlQueryModel *mdlRecords;
    QSqlQueryModel *mdlFiles;
    CheckComboBox *cbThemes;
    CheckComboboxList *cblTags;
    CheckDatePicker *dateFrom;
    CheckDatePicker *dateTo;
    CheckLineEdit *leAuthor;
    CheckLineEdit *leName;    
    QTableView *tableViewRecord;
    QTableView *tableViewFile;
    QListWidget *traceList;    
    MyTracer *tracer;
    Watcher *watcher;
    QLabel *lTags;
    QString tempPath;

    void add(QStringList fileNames);
    void addRecord(QStringList &fileNames, ObjRecord &record);
    void addRecordAsync(QStringList &fileNames, ObjRecord &record);
    bool checkFileDuplicate(QString fileName, QString &out_inf);
    bool checkContinueDuplicate(QString fileName);
    void reinit_recordtable(QModelIndex index);
    bool checkDB();
    int getFileId();
    int getBookId();

protected slots:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:   
    void selection_changed(const QItemSelection &selected);

    void new_record();
    void open_record(QModelIndex index);
    void open_file(QModelIndex index);
    void open_record();    
    void open_file();        
    void open_last_view();
    void open_last_add();
    void delete_last_view();
    void delete_last_add();
    void open_favorites();
    void add_favorites();
    void delete_favorites();
    void delete_favorites_all();
    void find_file_duplicate();
    void update_record();
    void delete_file();
    void delete_record();
    void add_file();
    void convert_htmltopdf();

    void on_pushButtonFind_clicked();
    void on_pushButtonViewTrace_clicked();

    void set_newbook(int bookid);

    void htmltopdf_finished(QString filename);

signals:
    void book_added(int bookid);
};

#endif // MAINWIDGET_H
