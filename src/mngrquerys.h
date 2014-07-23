#ifndef MNGRQUERYS_H
#define MNGRQUERYS_H

#define NULL_STR "NULL"

#include <appresources.h>
#include <objrecord.h>
#include <objfile.h>

#include <QMap>
#include <QtSql>
#include <QFile>
#include <QVariant>
#include <QSqlQueryModel>
#include <QCryptographicHash>

class MngrQuerys
{

public:
    MngrQuerys();
    static int addBook(ObjRecord &record);
    static int addFile(int bookId, QString fileName);
    static int updateFile(ObjFile &file, quint64 uzip_size);
    static int updateBook(ObjRecord &record);
    static int addTag(int bookId, QString name);
    static int addUserFindTag(int tagId);
    static int deleteUserFindTags();
    static int deleteLastViewBooks();
    static int deleteLastAddBooks();
    static int deleteFavoritesBooks();
    static int deleteFavoritesBook(int bookId);
    static int deleteTags(int bookId);
    static int deleteFile(int fileId);
    static int deleteBook(int bookId);
    static int addLastViewBook(int bookId);
    static int addLastAddBook(int bookId);
    static int addFavoriteBook(int bookId);    
    static int findFileDuplicate(QString fileName, QString &inf);
    static QStringList getThemes();
    static QStringList getTags();
    static QStringList getTagsBook(int bookid);
    static QMap<QString, int> getThemesId();
    static QMap<QString, int> getTagsId();
    static void setRecordModel(QSqlQueryModel &model, QVariant name, QVariant author, QVariant theme, QVariant datefrom, QVariant dateto, QVariant flagtag);
    static void setRecordModelNewBook(QSqlQueryModel &model, int bookId);
    static void setFileModel(QSqlQueryModel &model, int bookid);
    static void getFiles(int bookid, QList<ObjFile*> &files);
    static void getFile(int fileid, ObjFile &file);
    static void setRecordModelLastView(QSqlQueryModel &model);
    static void setRecordModelLastAdd(QSqlQueryModel &model);
    static void setRecordModelFavorites(QSqlQueryModel &model);    
};

#endif // MNGRQUERYS_H
