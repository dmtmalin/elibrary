#include "mytracer.h"

MyTracer::MyTracer(QObject *parent, QListWidget *list) :
    QObject(parent)
{    
    this->list = list;
}

void MyTracer::critical(QString const &text){
    if(this->list == 0) {
        return;
    }
    this->addItem(Qt::red, text);
}

void MyTracer::warning(QString const &text){
    if(this->list == 0) {
        return;
    }
    this->addItem(Qt::darkYellow, text);
}

void MyTracer::information(QString const &text){
    if(this->list == 0) {
        return;
    }
    this->addItem(Qt::black, text);
}

void MyTracer::OK(){
    if(this->list == 0) {
        return;
    }
    this->addItem(Qt::green, "OK");
}

void MyTracer::critical_slot(const QString &text){
    this->critical(text);
}

void MyTracer::warning_slot(const QString &text){
    this->warning(text);
}

void MyTracer::information_slot(const QString &text){
    this->information(text);
}

void MyTracer::OK_slot(){
    this->OK();
}

void MyTracer::critical_invoke(const QString &text){
     QMetaObject::invokeMethod(this, "critical_slot", Q_ARG(QString const&, text));
}

void MyTracer::warning_invoke(const QString &text){
    QMetaObject::invokeMethod(this, "warning_slot", Q_ARG(QString const&, text));
}

void MyTracer::information_invoke(const QString &text){
    QMetaObject::invokeMethod(this, "information_slot", Q_ARG(QString const&, text));
}

void MyTracer::OK_invoke(){
    QMetaObject::invokeMethod(this, "OK_slot");
}

void MyTracer::addItem(Qt::GlobalColor color, QString const &text){
    QString time = QTime::currentTime().toString();
    QString msec = QString::number(QTime::currentTime().msec());
    QString timemsec = QString("%1.%2: ").arg(time, msec);
    QString message = timemsec + text;
    QListWidgetItem* pItem = new QListWidgetItem(message);
    pItem->setForeground(color);
    this->list->addItem(pItem);
    this->list->scrollToBottom();
}
