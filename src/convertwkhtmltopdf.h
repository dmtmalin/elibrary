#ifndef CONVERTWKHTMLTOPDF_H
#define CONVERTWKHTMLTOPDF_H

#include <appresources.h>
#include <mytracer.h>

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QApplication>
#include <QDialogButtonBox>

class ConvertWkhtmltopdf : public QDialog
{
    Q_OBJECT
public:
    explicit ConvertWkhtmltopdf(QWidget *parent = 0, MyTracer *tracer = 0, QString tempPath = "");
    ~ConvertWkhtmltopdf();

private:
    QStringList getArguments();

    MyTracer *tracer;

    QLineEdit *nameLineEdit;
    QLineEdit *urlLineEdit;
    QListWidget *urlsList;

    QProcess *process;

    QString tempPath;

private slots:
    void on_buttonAddUrl_clicked();
    void on_buttonDeleteUrl_clicked();

    void on_accept();
    void on_reject();

    void ready_read_output();
    void ready_read_error();

    void finished_process(int exitCode);

signals:
    void finished(QString filename);

};

#endif // CONVERTWKHTMLTOPDF_H
