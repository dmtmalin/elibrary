#ifndef MNGRCONNECTION_H
#define MNGRCONNECTION_H

#include <appsettings.h>

#include <QtSql>
#include <QSettings>
#include <QApplication>

class MngrConnection
{
public:
    static MngrConnection& Instance() {
        static MngrConnection theSingleInstance;
        return theSingleInstance;
    }

    QString lastError();
    bool open();
    void close();
    bool transaction();
    bool commit();
    bool rollback();
    bool isOpen();

private:
    MngrConnection();    
    MngrConnection(const AppSettings& root);
    MngrConnection& operator=(const AppSettings&);

    QSqlDatabase db;
};

#endif // MNGRCONNECTION_H
