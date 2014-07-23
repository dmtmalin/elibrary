#include "mngrquerys.h"

MngrQuerys::MngrQuerys()
{
}

int MngrQuerys::addBook(ObjRecord &record) {
    int bookid = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_BOOK (?, ?, ?, ?)");
    query.addBindValue(record.getName());
    query.addBindValue(record.getAuthor());
    query.addBindValue(record.getTheme());
    query.addBindValue(record.getDescription());
    if(query.exec()) {
        query.next();
        bookid = query.value(0).toInt();
    }
    return bookid;
}

int MngrQuerys::updateBook(ObjRecord &record){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE UPDATE_BOOK (?, ?, ?, ?, ?)");
    query.addBindValue(record.getId());
    query.addBindValue(record.getName());
    query.addBindValue(record.getAuthor());
    query.addBindValue(record.getTheme());
    query.addBindValue(record.getDescription());
    if(query.exec()){
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::addFile(int bookId, QString fileName) {
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly))
        return -1;
    QByteArray arr = file->readAll();
    delete file;
    qint64 fSize = arr.size();
    QByteArray byte_md5  = QCryptographicHash::hash(arr, QCryptographicHash::Md5);
    QString md5 = QString(byte_md5.toHex());

    QByteArray zip_arr = qCompress(arr);
    qint64 fSize_zip = zip_arr.size();

    QFileInfo fInfo(fileName);
    QString fName = fInfo.fileName();
    QString fFormat = fInfo.suffix();    
    if(fFormat.isNull())
        fFormat = "";    

    int fileId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_FILE (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(bookId);
    query.addBindValue(fSize);
    query.addBindValue(fSize_zip);
    query.addBindValue(fName);
    query.addBindValue(fFormat);
    query.addBindValue(zip_arr);
    query.addBindValue(md5);
    if(query.exec()) {
        query.next();
        fileId = query.value(0).toInt();
    }
    return fileId;
}

int MngrQuerys::findFileDuplicate(QString fileName, QString &inf){
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly))
        return -2;
    QByteArray arr = file->readAll();
    delete file;
    QByteArray byte_md5  = QCryptographicHash::hash(arr, QCryptographicHash::Md5);
    QString md5 = QString(byte_md5.toHex());

    int fileId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE FIND_FILE_DUPLICATE (?)");
    query.addBindValue(md5);
    if(query.exec()) {
        query.next();
        fileId = query.value(0).toInt();
        inf = QString(QObject::tr("Название записи: %1 автор: %2 тема: %3")).arg(
                    query.value(1).toString()
                    ,query.value(2).toString()
                    ,query.value(3).toString());
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

int MngrQuerys::addUserFindTag(int tagId){
    int userFindTagId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_TO_USERFINDTAGS (?)");
    query.addBindValue(tagId);
    if(query.exec()) {
        query.next();
        userFindTagId = query.value(0).toInt();
    }
    return userFindTagId;
}

int MngrQuerys::deleteUserFindTags(){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_USERFINDTAGS");
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::deleteLastViewBooks(){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_LAST_VIEW_BOOKS");
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::deleteLastAddBooks(){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_LAST_ADD_BOOKS");
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::deleteFavoritesBooks(){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_FAVORITES_BOOKS");
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::deleteTags(int bookId){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_TAGS (?)");
    query.addBindValue(bookId);
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::deleteFile(int fileId){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_FILE (?)");
    query.addBindValue(fileId);
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::deleteBook(int bookId){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_BOOK (?)");
    query.addBindValue(bookId);
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::deleteFavoritesBook(int bookId){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE DELETE_FAVORITES_BOOK (?)");
    query.addBindValue(bookId);
    if(query.exec()) {
        query.next();
        result = query.value(0).toInt();
    }
    return result;
}

int MngrQuerys::updateFile(ObjFile &file, quint64 uzip_size){
    int result = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE UPDATE_BLOB (?, ?, ?, ?, ?)");
    query.addBindValue(file.getId());
    query.addBindValue(file.getMd5());
    query.addBindValue(uzip_size);
    query.addBindValue(file.getSize());
    query.addBindValue(file.getArray());
    if(query.exec()){
        query.next();
        result = query.value(0).toInt();
    }
    return result;
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

void MngrQuerys::setRecordModel(QSqlQueryModel &model, QVariant name, QVariant author, QVariant theme, QVariant datefrom, QVariant dateto, QVariant flagtag){
    QString query = "SELECT p.R_BOOKID, p.R_DATE, p.R_TIME, p.R_NAME, p.R_AUTHOR, p.R_THEME, p.R_DESCRIPTION FROM LIST_BOOK(%1, %2, %3, %4, %5, %6) p";
    query = query.arg(
                name.canConvert(QVariant::String) ? '\'' + name.toString() + '\'' : NULL_STR,
                author.canConvert(QVariant::String) ? '\'' + author.toString() + '\'' : NULL_STR,
                theme.canConvert(QVariant::Int) ? theme.toString() : NULL_STR,
                datefrom.canConvert(QVariant::String) ? '\'' + datefrom.toString() +'\'' : NULL_STR,
                dateto.canConvert(QVariant::String) ? '\'' + dateto.toString() + '\'' : NULL_STR,
                flagtag.canConvert(QVariant::Int) ? flagtag.toString() : NULL_STR);
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getDateStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getTimeStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(4, Qt::Horizontal, AppResources::getAuthorStr());
    model.setHeaderData(5, Qt::Horizontal, AppResources::getThemeStr());
    model.setHeaderData(6, Qt::Horizontal, AppResources::getDescriptionStr());
}

void MngrQuerys::setRecordModelNewBook(QSqlQueryModel &model, int bookId){
    QString query = "SELECT p.R_BOOKID, p.R_DATE, p.R_TIME, p.R_NAME, p.R_AUTHOR, p.R_THEME, p.R_DESCRIPTION FROM GET_BOOK (%1) p";
    query = query.arg(bookId);
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getDateStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getTimeStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(4, Qt::Horizontal, AppResources::getAuthorStr());
    model.setHeaderData(5, Qt::Horizontal, AppResources::getThemeStr());
    model.setHeaderData(6, Qt::Horizontal, AppResources::getDescriptionStr());
}

void MngrQuerys::setRecordModelLastAdd(QSqlQueryModel &model){
    QString query = "SELECT p.R_BOOKID, p.R_DATE, p.R_TIME, p.R_NAME, p.R_AUTHOR, p.R_THEME, p.R_DESCRIPTION FROM LIST_LAST_ADD_BOOKS p";
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getDateStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getTimeStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(4, Qt::Horizontal, AppResources::getAuthorStr());
    model.setHeaderData(5, Qt::Horizontal, AppResources::getThemeStr());
    model.setHeaderData(6, Qt::Horizontal, AppResources::getDescriptionStr());
}

void MngrQuerys::setRecordModelLastView(QSqlQueryModel &model){
    QString query = "SELECT p.R_BOOKID, p.R_DATE, p.R_TIME, p.R_NAME, p.R_AUTHOR, p.R_THEME, p.R_DESCRIPTION FROM LIST_LAST_VIEW_BOOKS p";
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getDateStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getTimeStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(4, Qt::Horizontal, AppResources::getAuthorStr());
    model.setHeaderData(5, Qt::Horizontal, AppResources::getThemeStr());
    model.setHeaderData(6, Qt::Horizontal, AppResources::getDescriptionStr());
}

void MngrQuerys::setRecordModelFavorites(QSqlQueryModel &model){
    QString query = "SELECT p.R_BOOKID, p.R_DATE, p.R_TIME, p.R_NAME, p.R_AUTHOR, p.R_THEME, p.R_DESCRIPTION FROM LIST_FAVORITES_BOOKS p";
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getDateStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getTimeStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(4, Qt::Horizontal, AppResources::getAuthorStr());
    model.setHeaderData(5, Qt::Horizontal, AppResources::getThemeStr());
    model.setHeaderData(6, Qt::Horizontal, AppResources::getDescriptionStr());
}

void MngrQuerys::setFileModel(QSqlQueryModel &model, int bookid){
    QString query = "SELECT p.ID, p.NAME, p.FORMAT, p.SIZEKB, p.SIZEKB_ZIP FROM GET_FILES_BOOK(%1) p";
    query = query.arg(bookid);
    model.setQuery(query);
    model.setHeaderData(1, Qt::Horizontal, AppResources::getNameStr());
    model.setHeaderData(2, Qt::Horizontal, AppResources::getFormatStr());
    model.setHeaderData(3, Qt::Horizontal, AppResources::getSizeStr());
    model.setHeaderData(4, Qt::Horizontal, AppResources::getSizeZipStr());
}

void MngrQuerys::getFiles(int bookid, QList<ObjFile*> &files){
    QSqlQuery query;
    query.prepare("SELECT p.ID, p.MD5, p.FILENAME, p.R_BLOB FROM GET_BLOBS(?) p");
    query.addBindValue(bookid);
    if(query.exec()) {
        while(query.next()) {
            int id = query.value(0).toInt();
            QString md5 = query.value(1).toString();
            QString name = query.value(2).toString();
            QByteArray zip_arr = query.value(3).toByteArray();
            QByteArray arr = qUncompress(zip_arr);
            ObjFile *file = new ObjFile("", name, md5, arr, id);
            files.append(file);
        }
    }
}

void MngrQuerys::getFile(int fileid, ObjFile &file){
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE GET_BLOB(?)");
    query.addBindValue(fileid);
    if(query.exec()) {
        query.next();
        int id = query.value(0).toInt();
        QString md5 = query.value(1).toString();
        QString name = query.value(2).toString();
        QByteArray zip_arr = query.value(3).toByteArray();
        QByteArray arr = qUncompress(zip_arr);
        file.setId(id);
        file.setMd5(md5);
        file.setName(name);
        file.setArray(arr);

    }
}

int MngrQuerys::addLastViewBook(int bookId){
    int usersBookId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_LAST_VIEW_BOOK (?)");
    query.addBindValue(bookId);
    if(query.exec()) {
        query.next();
        usersBookId = query.value(0).toInt();
    }
    return usersBookId;
}

int MngrQuerys::addLastAddBook(int bookId){
    int usersBookId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_LAST_ADD_BOOK (?)");
    query.addBindValue(bookId);
    if(query.exec()) {
        query.next();
        usersBookId = query.value(0).toInt();
    }
    return usersBookId;
}

int MngrQuerys::addFavoriteBook(int bookId){
    int usersBookId = 0;
    QSqlQuery query;
    query.prepare("EXECUTE PROCEDURE ADD_FAVORITE_BOOK (?)");
    query.addBindValue(bookId);
    if(query.exec()) {
        query.next();
        usersBookId = query.value(0).toInt();
    }
    return usersBookId;
}
