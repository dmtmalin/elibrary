#include "appsettings.h"

AppSettings::AppSettings()
{        
    QString application_dir = QApplication::applicationDirPath();
    QString settings_path = application_dir + "/settings.ini";

    settings = new QSettings(settings_path, QSettings::IniFormat);

    //settings->setValue("database", "/ELIBRARY.FDB");
    //settings->setValue("username", "SYSDBA");
    //settings->setValue("password", "masterkey");
    //settings->setValue("log", "true");

    db_path = application_dir + settings->value("database", "").toString();
    username = settings->value("username", "").toString();
    password = settings->value("password", "").toString();
    isLog = settings->value("log", "true").toBool();

}

QString AppSettings::getDB_path(){
    return db_path;
}


QString AppSettings::getUsername(){
    return username;
}

QString AppSettings::getPassword(){
    return password;
}

bool AppSettings::getIsLog(){
    return isLog;
}

AppSettings::~AppSettings(){
    delete settings;
}

