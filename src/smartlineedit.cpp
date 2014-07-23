#include "smartlineedit.h"
#include <QDebug>

SmartLineEdit::SmartLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    start = 0;
    countText = 0;
    single_mode = false;
    connect(this, SIGNAL(textEdited(const QString &)), this, SLOT(lineEdit_textEdited(const QString &)));

}

void SmartLineEdit::lineEdit_textEdited(const QString &text) {
    int n = text.count();
    if(n > 0) {
        if(text[n - 1] == ',' || text[n - 1] == ';' || text[n - 1] == '.') {
            if(single_mode) {
                this->setText(text.left(n - 1));
            }
            else {
                start = text.count();
            }
        }
    }
    else {
        start = 0;
    }
    autosubstitution(start, text);
}

void SmartLineEdit::selection(int start) {
    QString line = this->text();
    QString new_line = line.mid(start);
    if(!new_line.isEmpty()) {
        QString text = new_line.left(countText);
        int index = array->indexOf(new_line);
        if(key == Qt::Key_Up) {
            for(int i(index - 1); i > 0; --i) {
                if(set_selection(start, i, line, text)) {
                    return;
                }
            }
        }
        else if (key == Qt::Key_Down) {
            for(int i(index + 1); i< array->count(); ++i) {
                if(set_selection(start, i, line, text)) {
                    return;
                }
            }
        }
    }
}

bool SmartLineEdit::set_selection(int start, int i, QString line, QString text) {
    bool select = false;
    QString str = array->at(i);
    if(str.left(countText) == text) {
        QString new_str = line.left(start) + str;
        this->setText(new_str);
        this->setSelection(start + countText, str.count() - 1);
        select = true;
    }
    return select;
}

void SmartLineEdit::autosubstitution(int start, const QString &line){
    if(array != NULL && !line.isEmpty()) {
        QString text = line.mid(start);
        countText = text.count();
        for(int i(0); i < array->count(); ++i) {
            QString str = array->at(i);
            if(!text.isEmpty() && (key != Qt::Key_Backspace)  && str.left(countText) == text) {
                QString new_str = line.left(start) + str;
                this->setText(new_str);
                this->setSelection(start + countText, str.count() - 1);
                return;
            }
        }
    }
}

void SmartLineEdit::setArrayValues(const QStringList &arr){
    QString text;
    for(int i(0); i < arr.count(); ++i){
        text += arr.at(i) + ',';
    }
    text.remove(text.count() - 1, 1);
    this->setText(text);
}

void SmartLineEdit::setArray(const QStringList &arr) {
    this->array = new QStringList(arr);
}

void SmartLineEdit::setSingleMode() {
    this->single_mode = true;
}

void SmartLineEdit::keyPressEvent(QKeyEvent *event) {
    key = event->key();
    if(key == Qt::Key_Up || key == Qt::Key_Down) {
        selection(start);
    }
    else
        QLineEdit::keyPressEvent(event);


}

QStringList SmartLineEdit::getArrayValues() {    
    QRegExp rx("(\\,|\\;|\\.)");
    QString text = this->text().remove(' ');
    QStringList array = text.split(rx);
    return array;
}

QStringList SmartLineEdit::getArray() {
    return *array;
}

SmartLineEdit::~SmartLineEdit(){
    delete this->array;
}
