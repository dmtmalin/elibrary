#include "objrecord.h"

ObjRecord::ObjRecord(QString name,
                     QString author,
                     QString theme,
                     QString description,
                     QStringList *tags,
                     int id)
{
    this->name = name;
    this->author = author;
    this->theme = theme;
    this->description = description;
    if(tags != 0)
        this->tags = *tags;
    this->id = id;
}

ObjRecord::ObjRecord(QString name,
                     QString author,
                     QString theme,
                     QString description,
                     QStringList tags,
                     int id)
{
    this->name = name;
    this->author = author;
    this->theme = theme;
    this->description = description;
    this->tags = tags;
    this->id = id;
}

void ObjRecord::setName(QString name){
    this->name = name;
}

void ObjRecord::setAuthor(QString author){
    this->author = author;
}

void ObjRecord::setTheme(QString theme){
    this->theme = theme;
}

void ObjRecord::SetDescription(QString description){
    this->description = description;
}

void ObjRecord::setTags(QStringList tags){
    this->tags = tags;
}

void ObjRecord::setId(int id){
    this->id = id;
}

QString ObjRecord::getName(){
    return this->name;
}

QString ObjRecord::getAuthor(){
    return this->author;
}

QString ObjRecord::getTheme(){
    return this->theme;
}

QString ObjRecord::getDescription(){
    return this->description;
}

QStringList ObjRecord::getTags(){
    return this->tags;
}

int ObjRecord::getId(){
    return this->id;
}
