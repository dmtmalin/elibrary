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
    static const QString getAddThemeTagsStr();
    static const QString getAddFilesStr();
    static const QString getAddBookReportStr();
    static const QString getMenuStr();
    static const QString getMenuNewRecordStr();
    static const QString getFiltersStr();
    static const QString getTagStr();
    static const QString getRecordsStr();
    static const QString getFilesStr();
    static const QString getFindStr();
    static const QString getDateStr();
    static const QString getTimeStr();
    static const QString getFormatStr();
    static const QString getSizeStr();
    static const QString getOpenRecordStr();
    static const QString getOpenFileStr();
};

#endif // APPRESOURCES_H
