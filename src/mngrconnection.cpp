#include "mngrconnection.h"

MngrConnection::MngrConnection()
{   
    QString db_path = AppSettings::Instance().getDB_path();
    QString username = AppSettings::Instance().getUsername();
    QString password = AppSettings::Instance().getPassword();

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

QString MngrConnection::lastError() {
    return db.lastError().text();
}
