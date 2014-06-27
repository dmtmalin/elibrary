#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>

class FileUtils
{
public:
    static bool removeDir(const QString &dirName);
};

#endif // FILEUTILS_H
