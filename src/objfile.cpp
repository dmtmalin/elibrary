#include "objfile.h"

ObjFile::ObjFile(const QString path,
                 const QString name,
                 const QString md5,
                 QByteArray arr,
                 int id)
{
    this->arr = arr;
    this->size = this->arr.size();
    this->path = path;
    this->name = name;
    this->md5 = md5;
    this->id = id;
}

ObjFile::ObjFile(ObjFile &objfile){
    this->arr = objfile.getArray();
    this->size = this->arr.size();
    this->path = objfile.getPath();
    this->name = objfile.getName();
    this->md5 = objfile.getMd5();
    this->id = objfile.getId();
}

ObjFile::ObjFile(ObjFile *objfile){
    this->arr = objfile->getArray();
    this->size = this->arr.size();
    this->path = objfile->getPath();
    this->name = objfile->getName();
    this->md5 = objfile->getMd5();
    this->id = objfile->getId();
}

void ObjFile::setPath(const QString &path){
    this->path = path;
}

void ObjFile::setName(const QString &name){
    this->name = name;
}

void ObjFile::setArray(const QByteArray &arr){    
    this->arr = arr;
    this->size = arr.size();
}

void ObjFile::setMd5(const QString &md5){
    this->md5 = md5;
}

void ObjFile::setId(const int &id){
    this->id = id;
}

QByteArray ObjFile::getArray(){
    return this->arr;
}

QString ObjFile::getName(){
    return this->name;
}

QString ObjFile::getMd5(){
    return this->md5;
}

QString ObjFile::getPath(){
    return this->path;
}

quint64 ObjFile::getSize(){
    return this->size;
}

int ObjFile::getId(){
    return this->id;
}
