#include "appresources.h"

AppResources::AppResources()
{
}

const QString AppResources::getNameStr() {
    return QObject::tr("Название");
}

const QString AppResources::getAuthorStr() {
    return QObject::tr("Автор");
}

const QString AppResources::getThemeStr() {
    return QObject::tr("Тема");
}

const QString AppResources::getTagsStr() {
    return QObject::tr("Теги (,||.||;)");
}

const QString AppResources::getDescriptionStr() {
    return QObject::tr("Описание");
}

const QString AppResources::getAddThemeTagsStr() {
    return QObject::tr("+ из справочника");
}

const QString AppResources::getAddFilesStr() {
    return QObject::tr("+ файлы");
}

const QString AppResources::getAddBookReportStr() {
    return QObject::tr("Запись %1 добавлена\n• Автор: %2\n• Тема: %3");
}

const QString AppResources::getMenuStr() {
    return QObject::tr("&Меню");
}

const QString AppResources::getMenuNewRecordStr() {
    return QObject::tr("&Новая запись");
}

const QString AppResources::getFiltersStr() {
    return QObject::tr("Фильтры");
}

const QString AppResources::getTagStr() {
    return QObject::tr("Тег");
}

const QString AppResources::getRecordsStr(){
    return QObject::tr("Записи");
}

const QString AppResources::getFilesStr() {
    return QObject::tr("Файлы");
}

const QString AppResources::getFindStr() {
    return QObject::tr("Найти (Ctrl+F)");
}

const QString AppResources::getDateStr() {
    return QObject::tr("Дата");
}

const QString AppResources::getTimeStr() {
    return QObject::tr("Время");
}

const QString AppResources::getFormatStr() {
    return QObject::tr("Формат");
}

const QString AppResources::getSizeStr() {
    return QObject::tr("Размер,Kb");
}

const QString AppResources::getOpenRecordStr() {
    return QObject::tr("Открыть запись");
}

const QString AppResources::getOpenFileStr() {
    return QObject::tr("Открыть файл");
}
