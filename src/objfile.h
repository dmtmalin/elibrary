#ifndef OBJFILE_H
#define OBJFILE_H

#include <QObject>

class ObjFile
{
public:
    ObjFile(const QString path = "",
            const QString name = "",
            const QString md5 = "",
            QByteArray arr = (const char*)0,
            int id = 0);

    ObjFile(ObjFile &objfile);
    ObjFile(ObjFile *objfile);

    void setArray(const QByteArray &arr);
    void setPath(const QString &path);
    void setName(const QString &name);    
    void setMd5(const QString &md5);
    void setId(const int &id);

    QByteArray getArray();
    QString getPath();
    QString getName();
    QString getMd5();
    quint64 getSize();
    int getId();

private:
    QByteArray arr;
    QString path;
    QString name;
    QString md5;
    quint64 size;
    int id;
};

#endif // OBJFILE_H
