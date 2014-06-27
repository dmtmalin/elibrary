#include "mngrconnection.h"

MngrConnection::MngrConnection()
{
    QString application_dir = QApplication::applicationDirPath();
    QString settings_path = application_dir + "/settings.ini";
    QSettings settings(settings_path, QSettings::IniFormat);
    //settings.setValue("database", "/ELIBRARY.FDB");
    //settings.setValue("username", "SYSDBA");
    //settings.setValue("password", "masterkey");
    QString db_path = application_dir + settings.value("database", "").toString();
    QString username = settings.value("username", "").toString();
    QString password = settings.value("password", "").toString();

    db = QSqlDatabase::addDatabase("QIBASE");
    db.setDatabaseName(db_path);
    db.setUserName(username);
    db.setPassword(password);
}

bool MngrConnection::open()
{
    bool result = false;
    result = db.open();
    return result;
}

void MngrConnection::close()
{
    db.close();
}

bool MngrConnection::transaction() {
    bool result = false;
    result = db.transaction();
    return result;
}

bool MngrConnection::commit() {
    bool result = false;
    result = db.commit();
    return result;
}

bool MngrConnection::rollback() {
    bool result = false;
    result = db.rollback();
    return result;
}

bool MngrConnection::isOpen() {
    return db.isOpen();
}

QSqlError MngrConnection::lastError() {
    return db.lastError().text();
}
