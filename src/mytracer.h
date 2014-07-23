#ifndef MYTRACER_H
#define MYTRACER_H

#include <QTime>
#include <QObject>
#include <QListWidget>
#include <QMetaObject>
#include <QListWidgetItem>

class MyTracer : public QObject
{
    Q_OBJECT
public:
    explicit MyTracer(QObject *parent = 0, QListWidget *list = 0);

public:
    void critical(QString const &text);
    void warning(QString const &text);
    void information(QString const &text);
    void OK();

    void critical_invoke(QString const &text);
    void warning_invoke(QString const &text);
    void information_invoke(QString const &text);
    void OK_invoke();


private slots:
    void critical_slot(QString const &text);
    void warning_slot(QString const &text);
    void information_slot(QString const &text);
    void OK_slot();

private:
    void addItem(enum Qt::GlobalColor color, const QString &text);
    QListWidget *list;
};

#endif // MYTRACER_H
