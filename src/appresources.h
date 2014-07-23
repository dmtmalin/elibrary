#ifndef APPRESOURCES_H
#define APPRESOURCES_H

#include <QtCore>
#include <QObject>

class AppResources
{
public:
    AppResources();
    static const QString getNameStr();
    static const QString getAuthorStr();
    static const QString getThemeStr();
    static const QString getTagsStr();
    static const QString getDescriptionStr(); 
    static const QString getAddFilesStr();
    static const QString getNewRecordStr();
    static const QString getFiltersStr();
    static const QString getTagStr();
    static const QString getMenuStr();
    static const QString getRecordsStr();
    static const QString getFilesStr();
    static const QString getFileStr();
    static const QString getRecordStr();
    static const QString getFindStr();
    static const QString getDateStr();
    static const QString getTimeStr();
    static const QString getFormatStr();
    static const QString getSizeStr();
    static const QString getSizeZipStr();
    static const QString getOpenRecordStr();
    static const QString getOpenFileStr();
    static const QString getFavoritesStr();
    static const QString getTOPStr();
    static const QString getLastViewStr();
    static const QString getLastAddStr();
    static const QString getDeleteLastViewStr();
    static const QString getDeleteLastAddStr();
    static const QString getDeleteFavoritesStr();
    static const QString getDeleteFavoritesAllStr();
    static const QString getAddFavoritesStr();
    static const QString getViewFavoritesStr();
    static const QString getFileDuplicateStr();
    static const QString getDateToStr();
    static const QString getDateFromStr();
    static const QString getUpdateRecordStr();
    static const QString getDeleteRecordStr();
    static const QString getDeleteFileStr();
    static const QString getAddFileStr();
    static const QString getConvert();
    static const QString getHtmlToPDF();
    static const QString getURLStr();
    static const QString getProcessStart();
};

#endif // APPRESOURCES_H
