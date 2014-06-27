#ifndef SMARTLINEEDIT_H
#define SMARTLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

class SmartLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SmartLineEdit(QWidget *parent = 0);
    void setArray(const QStringList &arr);
    QStringList getArrayValues();
    QStringList getArray();
    void setSingleMode();
    QString getValue();
    ~SmartLineEdit();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QStringList *array = NULL;
    int countText, start, key;
    bool single_mode;
    void autosubstitution(int start, const QString &text);
    void selection(int start);
    bool set_selection(int start, int i, QString line, QString text);

private slots:
    void lineEdit_textEdited(const QString &text);
};

#endif // SMARTLINEEDIT_H
