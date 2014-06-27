#ifndef MNGRQUERYS_H
#define MNGRQUERYS_H

#define NULL_STR "NULL"

#include <appresources.h>

#include <QMap>
#include <QtSql>
#include <QFile>
#include <QVariant>
#include <QSqlQueryModel>

class MngrQuerys
{

public:
    MngrQuerys();
    static int addBook(QString name, QString author, QString theme, QString description);
    static int addFile(int bookId, QString fileName);
    static int addTag(int bookId, QString name);
    static QStringList getThemes();
    static QStringList getTags();
    static QStringList getTagsBook(int bookid);
    static QMap<QString, int> getThemesId();
    static QMap<QString, int> getTagsId();
    static void setRecordModel(QSqlQueryModel &model, QVariant name, QVariant author, QVariant theme, QVariant tag);
    static void setFileModel(QSqlQueryModel &model, int bookid);
    static void getFiles(int bookid, QMap<QString, QByteArray> &files);
    static void getFile(int fileid, QByteArray &arr, QString &name);
};

#endif // MNGRQUERYS_H
