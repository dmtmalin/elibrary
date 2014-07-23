#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>
#include <QApplication>

class AppSettings
{
public:   
    static AppSettings& Instance() {
        static AppSettings theSingleInstance;
        return theSingleInstance;
    }
    ~AppSettings();

    QString getDB_path();
    QString getPassword();
    QString getUsername();
    bool getIsLog();

private:
    AppSettings();
    AppSettings(const AppSettings& root);
    AppSettings& operator=(const AppSettings&);

    QSettings *settings;

    QString db_path;
    QString password;
    QString username;
    bool isLog;
};

#endif // APPSETTINGS_H
