#ifndef WATCHER_H
#define WATCHER_H

#include <mngrconnection.h>
#include <mngrquerys.h>
#include <mytracer.h>
#include <objfile.h>

#include <QFile>
#include <QTimer>
#include <QThread>
#include <QObject>
#include <QCryptographicHash>

#include <QDebug>

class Watcher : public QObject
{
    Q_OBJECT
public:
    Watcher(QObject *parent = 0, MyTracer *tracer = 0);
    ~Watcher();


public:
    void addFile(ObjFile &objfile);
    void addFile(ObjFile *objfile);
    void stopWatching();

private:
    QList<ObjFile*> *objfiles;
    MyTracer *tracer;
    QTimer *timer;
    QThread *nongui;
    QString path;

    bool check(ObjFile *objFile, quint64 &uzip_size);

private slots:
    void on_timer_timeout();

};

#endif // WATCHER_H
