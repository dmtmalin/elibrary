#include "mngrquerys.h"

MngrQuerys::MngrQuerys()
{
}

int MngrQuerys::addBook(QString name, QString author, QString theme, QString description) {
    int bookid = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_BOOK (?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(author);
    query.addBindValue(theme);
    query.addBindValue(description);
    if(query.exec()) {
        query.next();
        bookid = query.value(0).toInt();
    }
    return bookid;
}

int MngrQuerys::addFile(int bookId, QString fileName) {
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly))
        return -1;
    QByteArray arr = file->readAll();
    delete file;

    QByteArray zip_arr = qCompress(arr);
    qint64 fSize = zip_arr.size();

    QFileInfo fInfo(fileName);
    QString fName = fInfo.fileName();
    QString fFormat = fInfo.suffix();
    if(fFormat.isNull())
        fFormat = "";    

    int fileId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_FILE (?, ?, ?, ?, ?)");
    query.addBindValue(bookId);
    query.addBindValue(fSize);
    query.addBindValue(fName);
    query.addBindValue(fFormat);
    query.addBindValue(zip_arr);
    if(query.exec()) {
        query.next();
        fileId = query.value(0).toInt();
    }
    return fileId;
}

int MngrQuerys::addTag(int bookId, QString name) {
    int tagId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_BOOKTAG (?, ?)");
    query.addBindValue(bookId);
    query.addBindValue(name);
    if(query.exec()) {
        query.next();
        tagId = query.value(0).toInt();
    }
    return tagId;
}

QStringList MngrQuerys::getThemes() {
    QStringList themes;
    QSqlQuery query;
    query.prepare("SELECT p.NAME FROM GET_THEMES p");
    if(query.exec()) {
        while(query.next()) {
            QString theme = query.value(0).toString();
            themes.append(theme);
        }
    }
    return themes;
}

QStringList MngrQuerys::getTags() {
    QStringList tags;
    QSqlQuery query;
    query.prepare("SELECT p.NAME FROM GET_TAGS p");
    if(query.exec()) {
        while(query.next()) {
            QString tag = query.value(0).toString();
            tags.append(tag);
        }
    }
    return tags;
}

QStringList MngrQuerys::getTagsBook(int bookid){
    QStringList tags;
    QSqlQuery query;
    query.prepare("SELECT p.NAME FROM GET_TAGS_BOOK(?) p");
    query.addBindValue(bookid);
    if(query.exec()) {
        while(query.next()) {
            QString tag = query.value(0).toString();
            tags.append(tag);
        }
    }
    return tags;

}

QMap<QString, int> MngrQuerys::getThemesId(){
    QMap<QString, int> themes;
    QSqlQuery query;
    query.prepare("SELECT p.ID, p.NAME FROM GET_THEMES p");
    if(query.exec()) {
        while(query.next()) {
            int id = query.value(0).toInt();
            QString theme = query.value(1).toString();
            themes[theme] = id;
        }
    }
    return themes;
}

QMap<QString, int> MngrQuerys::getTagsId(){
    QMap<QString, int> tags;
    QSqlQuery query;
    query.prepare("SELECT p.ID, p.NAME FROM GET_TAGS p");
    if(query.exec()) {
        while(query.next()) {
            int id = query.value(0).toInt();
            QString tag = query.value(1).toString();
            tags[tag] = id;
        }
    }
    return tags;
}

void MngrQuerys::setRecordModel(QSqlQueryModel &model, QVariant name, QVariant author, QVariant theme, QVariant tag){
    QString query = "SELECT p.R_BOOKID, p.R_DATE, p.R_TIME, p.R_NAME, p.R_AUTHOR, p.R_THEME, p.R_DESCRIPTION FROM LIST_BOOK(%1, %2, %3, %4) p";
    query = query.arg(
                name.canConvert(QVariant::String) ? '\'' + name.toString() + '\'' : NULL_STR,
                author.canConvert(QVariant::String) ? '\'' + author.toString() + '\'' : NULL_STR,
                theme.canConvert(QVariant::Int) ? theme.toString() : NULL_STR,
                tag.canConvert(QVariant::Int) ? tag.toString() : NULL_STR);
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getDateStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getTimeStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(4, Qt::Horizontal, AppResources::getAuthorStr());
    model.setHeaderData(5, Qt::Horizontal, AppResources::getThemeStr());
    model.setHeaderData(6, Qt::Horizontal, AppResources::getDescriptionStr());
}

void MngrQuerys::setFileModel(QSqlQueryModel &model, int bookid){
    QString query = "SELECT p.ID, p.NAME, p.FORMAT, p.SIZEKB FROM GET_FILES_BOOK(%1) p";
    query = query.arg(bookid);
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getFormatStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getSizeStr());
}

void MngrQuerys::getFiles(int bookid, QMap<QString, QByteArray> &files){
    QSqlQuery query;
    query.prepare("SELECT p.FILENAME, p.R_BLOB FROM GET_BLOBS(?) p");
    query.addBindValue(bookid);
    if(query.exec()) {
        while(query.next()) {
            QString name = query.value(0).toString();
            QByteArray zip_arr = query.value(1).toByteArray();
            files[name] = qUncompress(zip_arr);
        }
    }
}

void MngrQuerys::getFile(int fileid, QByteArray &arr, QString &name){
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE GET_BLOB(?)");
    query.addBindValue(fileid);
    if(query.exec()) {
        query.next();
        name = query.value(1).toString();
        QByteArray zip_arr = query.value(2).toByteArray();
        arr = qUncompress(zip_arr);
    }
}
