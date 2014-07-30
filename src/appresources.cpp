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

const QString AppResources::getAddFilesStr() {
    return QObject::tr("+ файлы");
}

const QString AppResources::getNewRecordStr() {
    return QObject::tr("Новая запись");
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

const QString AppResources::getFileStr(){
     return QObject::tr("Файл");
}

const QString AppResources::getRecordStr(){
    return QObject::tr("Запись");
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
    return QObject::tr("Фактический размер,Kb");
}

const QString AppResources::getSizeZipStr(){
    return QObject::tr("Размер в базе,Kb");
}

const QString AppResources::getOpenRecordStr() {
    return QObject::tr("Открыть запись");
}

const QString AppResources::getOpenFileStr() {
    return QObject::tr("Открыть файл");
}

const QString AppResources::getFavoritesStr(){
    return QObject::tr("Избранное");
}

const QString AppResources::getTOPStr(){
    return QObject::tr("ТОП");
}

const QString AppResources::getMenuStr(){
    return QObject::tr("Меню");
}

const QString AppResources::getLastViewStr(){
    return QObject::tr("Показать последние открытые");
}

const QString AppResources::getLastAddStr(){
    return QObject::tr("Показать последние добавленные");
}

const QString AppResources::getDeleteLastViewStr(){
    return QObject::tr("Очистить последние открытые");
}

const QString AppResources::getDeleteLastAddStr(){
    return QObject::tr("Очистить последние добавленные");
}

const QString AppResources::getViewFavoritesStr(){
    return QObject::tr("Показать избранное");
}

const QString AppResources::getAddFavoritesStr(){
    return QObject::tr("Добавить в избранное");
}

const QString AppResources::getDeleteFavoritesStr(){
    return QObject::tr("Убрать из избранного");
}

const QString AppResources::getDeleteFavoritesAllStr(){
    return QObject::tr("Очистить избранное");
}

const QString AppResources::getFileDuplicateStr(){
    return QObject::tr("Поиск файла в БД");
}

const QString AppResources::getDateFromStr(){
    return QObject::tr("Дата с");
}

const QString AppResources::getDateToStr(){
    return QObject::tr("Дата по");
}

const QString AppResources::getUpdateRecordStr(){
    return QObject::tr("Редактировать запись");
}

const QString AppResources::getDeleteFileStr(){
    return QObject::tr("Удалить файл");
}

const QString AppResources::getAddFileStr(){
    return QObject::tr("Добавить файл");
}

const QString AppResources::getDeleteRecordStr(){
    return QObject::tr("Удалить запись");
}

const QString AppResources::getConvert(){
    return QObject::tr("Преобразование");
}

const QString AppResources::getHtmlToPDF(){
     return QObject::tr("Htmls->pdf (wkhtmltopdf)");
}

const QString AppResources::getURLStr(){
     return QObject::tr("URL");
}

const QString AppResources::getProcessStart(){
     return QObject::tr("wkhtmltopdf запущен");
}
