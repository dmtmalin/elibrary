#ifndef MNGRCONNECTION_H
#define MNGRCONNECTION_H

#include <QtSql>
#include <QSettings>
#include <QApplication>

class MngrConnection
{
public:
    MngrConnection();
    QSqlError lastError();
    bool open();
    void close();
    bool transaction();
    bool commit();
    bool rollback();
    bool isOpen();
private:
    QSqlDatabase db;
};

#endif // MNGRCONNECTION_H
