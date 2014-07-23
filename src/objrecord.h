#ifndef OBJRECORD_H
#define OBJRECORD_H

#include <QObject>
#include <QStringList>

class ObjRecord
{
public:
    ObjRecord(QString name = "",
              QString author = "",
              QString theme = "",
              QString description = "",
              QStringList *tags = 0,
              int id = 0);
    ObjRecord(QString name,
              QString author,
              QString theme,
              QString description,
              QStringList tags,
              int id = 0);

public:
    void setName(QString name);
    void setAuthor(QString author);
    void setTheme(QString theme);
    void SetDescription(QString description);
    void setTags(QStringList tags);
    void setId(int id);
    QString getName();
    QString getAuthor();
    QString getTheme();
    QString getDescription();
    QStringList getTags();
    int getId();

private:
    QString name;
    QString author;
    QString theme;
    QString description;
    QStringList tags;
    int id;
};

#endif // OBJRECORD_H
