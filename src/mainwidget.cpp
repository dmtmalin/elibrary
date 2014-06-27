#include "mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{    
    QMenuBar *menubar = new QMenuBar();    

    QAction *new_action = new QAction(QIcon(":/png/Add.png"), AppResources::getMenuNewRecordStr(), this);
    new_action->setShortcuts(QKeySequence::New);
    connect(new_action, SIGNAL(triggered()), this, SLOT(new_record()));

    QAction *open_record_action = new QAction(QIcon(":/png/Edit.png"), AppResources::getOpenRecordStr(), this);
    open_record_action->setShortcut(QKeySequence::Open);
    connect(open_record_action, SIGNAL(triggered()), this, SLOT(open_record()));

    QAction *open_file_action = new QAction(QIcon(":/png/Edit Alt.png"), AppResources::getOpenFileStr(), this);
    connect(open_file_action, SIGNAL(triggered()), this, SLOT(open_file()));

    QMenu *add = menubar->addMenu(AppResources::getMenuStr());
    add->addAction(new_action);
    add->addAction(open_record_action);
    add->addAction(open_file_action);

    QGroupBox *boxFilter = new QGroupBox(AppResources::getFiltersStr());   

    cbThemes = new CheckComboBox();
    cbThemes->setCheckBoxText(AppResources::getThemeStr());
    cbTags = new CheckComboBox();
    cbTags->setCheckBoxText(AppResources::getTagStr());
    leAuthor = new CheckLineEdit();
    leAuthor->setCheckBoxText(AppResources::getAuthorStr());
    leName = new CheckLineEdit();
    leName->setCheckBoxText(AppResources::getNameStr());

    QBoxLayout *boxFilterLayout = new QBoxLayout(QBoxLayout::Down);
    boxFilterLayout->addWidget(leName);
    boxFilterLayout->addWidget(leAuthor);
    boxFilterLayout->addWidget(cbThemes);
    boxFilterLayout->addWidget(cbTags);
    boxFilter->setLayout(boxFilterLayout);

    QGroupBox *boxRecord = new QGroupBox(AppResources::getRecordsStr());

    tableViewRecord = new QTableView();
    tableViewRecord->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewRecord->setSelectionMode(QAbstractItemView::SingleSelection);
    tableViewRecord->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mdlRecords = new QSqlQueryModel();
    tableViewRecord->setModel(mdlRecords);
    connect(tableViewRecord, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(open_record(QModelIndex)));
    connect(tableViewRecord->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(selection_changed(const QItemSelection &)));    

    lTags = new QLabel(AppResources::getTagStr());

    QBoxLayout *boxRecordLayout = new QBoxLayout(QBoxLayout::Down);
    boxRecordLayout->addWidget(tableViewRecord);
    boxRecordLayout->addWidget(lTags);
    boxRecord->setLayout(boxRecordLayout);

    QGroupBox *boxFile = new QGroupBox(AppResources::getFilesStr());

    tableViewFile = new QTableView();
    tableViewFile->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewFile->setSelectionMode(QAbstractItemView::SingleSelection);
    tableViewFile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mdlFiles = new QSqlQueryModel();
    tableViewFile->setModel(mdlFiles);
    connect(tableViewFile, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(open_file(QModelIndex)));

    QBoxLayout *boxFileLayout = new QBoxLayout(QBoxLayout::Down);
    boxFileLayout->addWidget(tableViewFile);
    boxFile->setLayout(boxFileLayout);

    QBoxLayout *layoutTable = new QBoxLayout(QBoxLayout::Down);
    layoutTable->addWidget(boxRecord);
    layoutTable->addWidget(boxFile);

    QBoxLayout *layoutFilterAndButton = new QBoxLayout(QBoxLayout::Down);
    layoutFilterAndButton->addWidget(boxFilter);
    layoutFilterAndButton->addStretch(1);

    QPushButton *pushButtonFind = new QPushButton(QIcon(":/png/Search.png"), AppResources::getFindStr());    
    connect(pushButtonFind, SIGNAL(clicked()), this, SLOT(on_pushButtonFind_clicked()));    
    QShortcut *pushFindShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), this);
    connect(pushFindShortcut, SIGNAL(activated()), pushButtonFind, SLOT(click()));

    layoutFilterAndButton->addWidget(pushButtonFind);

    QBoxLayout *layoutMain = new QBoxLayout(QBoxLayout::LeftToRight);
    layoutMain->addLayout(layoutFilterAndButton, 1);
    layoutMain->addLayout(layoutTable, 3);

    QGridLayout *pgrdLayout  = new QGridLayout();
    pgrdLayout->addWidget(menubar, 0, 0);
    pgrdLayout->addLayout(layoutMain, 1, 0);

    this->setLayout(pgrdLayout);
    this->setAcceptDrops(true);
    this->setWindowIcon(QIcon(":/Double-J-Design-Ravenna-3d-Book.ico"));

    int w = 1200;
    int h = 443;   
    int s_w = QApplication::desktop()->screen(0)->width();
    int s_h = QApplication::desktop()->screen(0)->height();
    this->setGeometry((s_w - w) / 2, (s_h - h) / 2, w, h);

    if(!mngrConnection.open()) {
        QMessageBox::critical(this, "DB connection", mngrConnection.lastError().text(), QMessageBox::Ok);
    }
    else {
        initCheckComboBoxs();
    }

    //create app temp folder
    tempPath = QDir::tempPath() + "/ELibrary";
    bool exists = QDir(tempPath).exists();
    if(!exists){
        QDir().mkdir(tempPath);
    }

}

void MainWidget::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWidget::dropEvent(QDropEvent *event){
    QStringList fileNames;
    foreach (QUrl url, event->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        fileNames.append(fileName);
    }
    mngrConnection.transaction();
    QStringList themes = MngrQuerys::getThemes();
    QStringList tags = MngrQuerys::getTags();
    mngrConnection.commit();
    addBook(fileNames, themes, tags);
    event->acceptProposedAction();
}

void MainWidget::open_file(){
    QModelIndexList indexes = tableViewFile->selectionModel()->selection().indexes();
    if(indexes.count() > 0) {
        open_file(indexes.at(0));
    }
}

void MainWidget::open_record() {
     QModelIndexList indexes  = tableViewRecord->selectionModel()->selection().indexes();
     if(indexes.count() > 0) {
           open_record(indexes.at(0));
     }
}

void MainWidget::open_file(QModelIndex index){
    int row = index.row();
    int fileid = mdlFiles->record(row).value(0).toInt();
    QByteArray arr;
    QString name;
    mngrConnection.transaction();
    MngrQuerys::getFile(fileid, arr, name);
    mngrConnection.commit();
    QString path = tempPath + '/' + name;
    if(!arr.isEmpty() && !name.isEmpty()) {
        if(!QFile::exists(path)){
            QFile file(path);
            file.open(QIODevice::WriteOnly);
            file.write(arr);
            file.close();
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
    else{
        QMessageBox::critical(this, "Open file", "File not open!", QMessageBox::Ok);
    }
}

void MainWidget::open_record(QModelIndex index){
    int row = index.row();
    int bookid = mdlRecords->record(row).value(0).toInt();
    QMap<QString, QByteArray> files;
    mngrConnection.transaction();
    MngrQuerys::getFiles(bookid, files);
    mngrConnection.commit();
    if(!files.isEmpty()) {
        QMapIterator<QString, QByteArray> i(files);
        while (i.hasNext()) {
            i.next();
            QString path = tempPath + '/' + i.key();
            if(!QFile::exists(path)) {
                QFile file(path);
                file.open(QIODevice::WriteOnly);
                file.write(i.value());
                file.close();
            }
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(tempPath));
    }
    else {
        QMessageBox::critical(this, "Open files", "Files not open!", QMessageBox::Ok);
    }
}

void MainWidget::initCheckComboBoxs() {    
    mngrConnection.transaction();
    QMap<QString, int> themes = MngrQuerys::getThemesId();
    QMap<QString, int> tags = MngrQuerys::getTagsId();
    mngrConnection.commit();
    cbThemes->setComboBoxItems(themes);
    cbTags->setComboBoxItems(tags);
}

void MainWidget::selection_changed(const QItemSelection &selected){
    QModelIndexList indexes = selected.indexes();
    if(!indexes.count() > 0) {
        return;
    }
    int row = indexes.at(0).row();
    int bookid = mdlRecords->record(row).value(0).toInt();
    QStringList tags = MngrQuerys::getTagsBook(bookid);
    QString text;
    for(int i(0); i < tags.count(); ++i){
        text += tags.at(i) + ',';
    }
    text.remove(text.count() - 1, 1);
    lTags->setText(AppResources::getTagStr()+ ": " + text);
    mngrConnection.transaction();
    MngrQuerys::setFileModel(*mdlFiles, bookid);
    mngrConnection.commit();
    tableViewFile->setColumnHidden(0, true);
}

void MainWidget::on_pushButtonFind_clicked(){
    QVariant name = leName->getValue();
    QVariant author = leAuthor->getValue();
    QVariant theme = cbThemes->getValue();
    QVariant tag = cbTags->getValue();
    mngrConnection.transaction();
    MngrQuerys::setRecordModel(*mdlRecords, name, author, theme, tag);
    mngrConnection.commit();
    tableViewRecord->setColumnHidden(0, true);
}

void MainWidget::new_record(){
    QFileDialog *dlgFile = new QFileDialog(this);
    dlgFile->setFileMode(QFileDialog::ExistingFiles);
    QStringList fileNames;
    if (dlgFile->exec() == QFileDialog::Accepted)
        fileNames = dlgFile->selectedFiles();
    delete dlgFile;
    if(!fileNames.count() > 0) {
        return;
    }
    mngrConnection.transaction();
    QStringList themes = MngrQuerys::getThemes();
    QStringList tags = MngrQuerys::getTags();
    mngrConnection.commit();
    addBook(fileNames, themes, tags);
}

void MainWidget::addBook(QStringList fileNames, QStringList themes, QStringList tags){    
    BookDialog *dlgBook = new BookDialog(this);
    dlgBook->setName(fileNames.at(0));
    dlgBook->setThemes(themes);
    dlgBook->setTags(tags);
    if(dlgBook->exec() == QDialog::Accepted) {
        QStringList addFileNames = dlgBook->getFileNames();
        for(int i(0); i < addFileNames.count(); ++i) {
             fileNames.append(addFileNames.at(i));
        }
        QString name = dlgBook->getName();
        QString author = dlgBook->getAuthor();
        QString theme = dlgBook->getTheme();
        QString description = dlgBook->getDescription();
        QStringList tags = dlgBook->getTags();
        delete dlgBook;
        if(mngrConnection.transaction()) {
            int bookId = MngrQuerys::addBook(name, author, theme, description);
            if(bookId > 0) {
                for(int i(0); i < fileNames.count(); ++i) {
                    int fileId = MngrQuerys::addFile(bookId, fileNames.at(i));
                    if(fileId == -1) {
                        QMessageBox::critical(this, "Open file", "Can't open file " + fileNames.at(i), QMessageBox::Ok);
                        mngrConnection.rollback();
                        return;
                    }
                    if(fileId == 0) {
                        QMessageBox::critical(this, "DB add file", mngrConnection.lastError().text(), QMessageBox::Ok);
                        mngrConnection.rollback();
                        return;
                    }
                }
                for(int i(0); i < tags.count(); ++i) {
                    int tagId = MngrQuerys::addTag(bookId, tags.at(i));
                    if(tagId == 0) {
                        QMessageBox::critical(this, "DB add tag", mngrConnection.lastError().text(), QMessageBox::Ok);
                        mngrConnection.rollback();
                        return;
                    }
                }
                mngrConnection.commit();
                addBookReport(name, author, theme);
                initCheckComboBoxs();
            }
            else
                mngrConnection.rollback();
        }
        else
            QMessageBox::critical(this, "DB transaction", mngrConnection.lastError().text(), QMessageBox::Ok);
    }
    else
        delete dlgBook;    
}

void MainWidget::addBookReport(QString name, QString author, QString theme) {
    QString build(AppResources::getAddBookReportStr());
    build = build.arg(name, author, theme);
    QMessageBox::information(this, "Info", build, QMessageBox::Ok);
}

void MainWidget::closeEvent(QCloseEvent *event) {
    mngrConnection.close();

    FileUtils::removeDir(tempPath);

    event->accept();
}

MainWidget::~MainWidget()
{   
}
