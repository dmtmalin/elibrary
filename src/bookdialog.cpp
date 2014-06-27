#include "bookdialog.h"

BookDialog::BookDialog(QWidget *parent)
    :QDialog(parent)
{
    QLabel *labelName = new QLabel(AppResources::getNameStr());
    QLabel *labelAuthor = new QLabel(AppResources::getAuthorStr());
    QLabel *labelTheme = new QLabel(AppResources::getThemeStr());
    QLabel *labelTags = new QLabel(AppResources::getTagsStr());
    QLabel *labelDescription = new QLabel(AppResources::getDescriptionStr());

    lineEditName = new QLineEdit();
    lineEditAuthor = new QLineEdit();
    lineEditTheme = new SmartLineEdit();
    lineEditTheme->setSingleMode();   
    lineEditTags = new SmartLineEdit();    
    textEditDescription = new QTextEdit();

    QPushButton *pushButtonAddTheme = new QPushButton(AppResources::getAddThemeTagsStr());
    connect(pushButtonAddTheme, SIGNAL(clicked()), this, SLOT(on_pushButtonAddTheme_clicked()));
    QPushButton *pushButtonAddTags = new QPushButton(AppResources::getAddThemeTagsStr());
    connect(pushButtonAddTags, SIGNAL(clicked()), this, SLOT(on_pushButtonAddTags_clicked()));
    QPushButton *pushButtonAddFiles = new QPushButton(AppResources::getAddFilesStr());
    connect(pushButtonAddFiles, SIGNAL(clicked()), this, SLOT(on_pushButtonAddFiles_clicked()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *pgrdLayout = new QGridLayout();
    pgrdLayout->addWidget(labelName, 0, 0);
    pgrdLayout->addWidget(lineEditName, 0, 1);
    pgrdLayout->addWidget(labelAuthor, 1, 0);
    pgrdLayout->addWidget(lineEditAuthor, 1, 1);
    pgrdLayout->addWidget(labelTheme, 2, 0);
    pgrdLayout->addWidget(lineEditTheme, 2, 1);
    pgrdLayout->addWidget(pushButtonAddTheme, 3, 1);
    pgrdLayout->addWidget(labelTags, 4, 0);
    pgrdLayout->addWidget(lineEditTags, 4, 1);
    pgrdLayout->addWidget(pushButtonAddTags, 5, 1);
    pgrdLayout->addWidget(labelDescription, 6, 0);
    pgrdLayout->addWidget(textEditDescription, 6, 1);
    pgrdLayout->addWidget(pushButtonAddFiles, 7, 0);
    pgrdLayout->addWidget(buttonBox, 7, 1);

    this->setLayout(pgrdLayout);

}

void BookDialog::on_pushButtonAddTheme_clicked() {
    ListWidgetDialogOne dlg;
    QStringList themes = lineEditTheme->getArray();
    dlg.setWidgetItems(themes);
    if(dlg.exec()) {
        QString text = dlg.getValueToString();
        if(!text.isEmpty())
            lineEditTheme->setText(text);
    }
}

void BookDialog::on_pushButtonAddTags_clicked() {
    ListWidgetDialog dlg;
    QStringList tags = lineEditTags->getArray();
    dlg.setWidgetItems(tags);
    if(dlg.exec()) {
        QString text = lineEditTags->text();
        QString str = dlg.getValuesToString();
        lineEditTags->setText(text + str);
    }
}

void BookDialog::on_pushButtonAddFiles_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec() == QFileDialog::Accepted)
        fileNames = dialog.selectedFiles();
}

QString BookDialog::getName() {
    return lineEditName->text();
}

QString BookDialog::getAuthor() {
    return lineEditAuthor->text();
}

QString BookDialog::getTheme() {
    return lineEditTheme->getArrayValues().at(0);
}

QString BookDialog::getDescription() {
    return textEditDescription->toPlainText();
}

QStringList BookDialog::getTags() {
    return lineEditTags->getArrayValues();
}

QStringList BookDialog::getFileNames() {
    return fileNames;
}

void BookDialog::setThemes(QStringList &arr) {
    lineEditTheme->setArray(arr);
}

void BookDialog::setTags(QStringList &arr) {
    lineEditTags->setArray(arr);
}

void BookDialog::setName(QString name){
    QFileInfo info(name);
    if(info.isFile()) {
        lineEditName->setText(info.fileName());
    }
}

BookDialog::~BookDialog()
{

}
