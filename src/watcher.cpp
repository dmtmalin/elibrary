#include "watcher.h"

Watcher::Watcher(QObject *parent, MyTracer *tracer) :
    QObject(parent)
{
    this->tracer = tracer;

    objfiles = new QList<ObjFile*>();

    nongui = new QThread(this);

    int inter = 1000;

    timer = new QTimer();
    timer->setInterval(inter);
    timer->moveToThread(nongui);

    connect(timer, SIGNAL(timeout()), SLOT(on_timer_timeout()), Qt::DirectConnection);
    connect(nongui, SIGNAL(started()), timer, SLOT(start()));
    connect(nongui, SIGNAL(finished()), timer, SLOT(deleteLater()));

    nongui->start();
}

void Watcher::on_timer_timeout(){
    timer->stop();
    for(int i(0); i < objfiles->count(); ++i){
        quint64 uzip_size;
        bool check = this->check(objfiles->at(i), uzip_size);
        if(check){
            if(tracer != 0){
                tracer->information_invoke(tr("Изменение файла... ") + objfiles->at(i)->getName());
            }
            MngrConnection::Instance().transaction();
            int res = MngrQuerys::updateFile(*objfiles->at(i), uzip_size);
            if(res > 0) {
                MngrConnection::Instance().commit();
                objfiles->at(i)->setArray((const char*)0);
                if(tracer != 0){
                   tracer->OK_invoke();
                }
            }
            else {
                MngrConnection::Instance().rollback();
                if(tracer != 0){
                  tracer->critical_invoke(MngrConnection::Instance().lastError());
                }
            }
        }
    }
    timer->start();
}

bool Watcher::check(ObjFile *objFile, quint64 &uzip_size){
    bool check = false;
    QString path = objFile->getPath();
    if(QFile::exists(path)){
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly))
            return check;
        QByteArray arr = file.readAll();
        QByteArray byte_md5  = QCryptographicHash::hash(arr, QCryptographicHash::Md5);
        QString new_md5 = QString(byte_md5.toHex());
        QString md5 = objFile->getMd5();
        if(md5 != new_md5){
            check = true;
            uzip_size = arr.size();
            QByteArray zip_arr = qCompress(arr);
            objFile->setArray(zip_arr);
            objFile->setMd5(new_md5);
        }
    }

    return check;

}

void Watcher::stopWatching(){    
    nongui->quit();    
}

void Watcher::addFile(ObjFile &objfile){
    ObjFile *file = new ObjFile(objfile);
    objfiles->append(file);
}

void Watcher::addFile(ObjFile *objfile){
    objfile->setArray((const char*)0);
    ObjFile *file = new ObjFile(objfile);
    objfiles->append(file);
}

Watcher::~Watcher(){
    for(int i(0); i < objfiles->count(); ++i)
        delete objfiles->at(i);
    delete objfiles;
    delete nongui;
}

