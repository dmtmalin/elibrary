#ifndef VIEWLISTWIDGET_H
#define VIEWLISTWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QListWidget>

class ViewListWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ViewListWidget(QWidget *parent = 0, QListWidget *list = 0);
    void scrollToBottom();

private:
    QListWidget *lw;

signals:

public slots:

};

#endif // VIEWLISTWIDGET_H
