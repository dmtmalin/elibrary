#include "mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{    
    QMenuBar *menubar = new QMenuBar();    

    QAction *new_action = new QAction(QIcon(":/png/Add.png"), AppResources::getNewRecordStr(), this);
    new_action->setShortcut(QKeySequence::New);
    connect(new_action, SIGNAL(triggered()), this, SLOT(new_record()));

    QAction *open_record_action = new QAction(QIcon(":/png/Edit Alt.png"), AppResources::getOpenRecordStr(), this);
    open_record_action->setShortcut(QKeySequence::Open);
    connect(open_record_action, SIGNAL(triggered()), this, SLOT(open_record()));

    QAction *open_file_action = new QAction(QIcon(":/png/Edit.png"), AppResources::getOpenFileStr(), this);
    connect(open_file_action, SIGNAL(triggered()), this, SLOT(open_file()));

    QAction *open_last_view_action = new QAction(QIcon(":/png/View.png"), AppResources::getLastViewStr(), this);
    connect(open_last_view_action, SIGNAL(triggered()), this, SLOT(open_last_view()));

    QAction *open_last_add_action = new QAction(QIcon(":/png/Add.png"), AppResources::getLastAddStr(), this);
    connect(open_last_add_action, SIGNAL(triggered()), this, SLOT(open_last_add()));

    QAction *delete_last_view_action = new QAction(QIcon(":/png/Delete.png"), AppResources::getDeleteLastViewStr(), this);
    connect(delete_last_view_action, SIGNAL(triggered()), this, SLOT(delete_last_view()));

    QAction *delete_last_add_action = new QAction(QIcon(":/png/Delete.png"), AppResources::getDeleteLastAddStr(), this);
    connect(delete_last_add_action, SIGNAL(triggered()), this, SLOT(delete_last_add()));

    QAction *delete_file_action = new QAction(QIcon(":/png/Delete.png"), AppResources::getDeleteFileStr(), this);
    connect(delete_file_action, SIGNAL(triggered()), this, SLOT(delete_file()));

    QAction *open_favorites_action = new QAction(QIcon(":/png/Favorites.png"), AppResources::getViewFavoritesStr(), this);
    connect(open_favorites_action, SIGNAL(triggered()), this, SLOT(open_favorites()));

    QAction *add_favorites_action = new QAction(QIcon(":/png/Favorites Add.png"), AppResources::getAddFavoritesStr(), this);
    connect(add_favorites_action, SIGNAL(triggered()), this, SLOT(add_favorites()));

    QAction *delete_favorites_action = new QAction(QIcon(":/png/Favorites Remove.png"), AppResources::getDeleteFavoritesStr(), this);
    connect(delete_favorites_action, SIGNAL(triggered()), this, SLOT(delete_favorites()));

    QAction *delete_favorites_all_action = new QAction(QIcon(":/png/Delete.png"), AppResources::getDeleteFavoritesAllStr(), this);
    connect(delete_favorites_all_action, SIGNAL(triggered()), this, SLOT(delete_favorites_all()));

    QAction *find_file_duplicate_action = new QAction(QIcon(":/png/Checkmark.png"), AppResources::getFileDuplicateStr(), this);
    connect(find_file_duplicate_action, SIGNAL(triggered()), this, SLOT(find_file_duplicate()));

    QAction *update_record_action = new QAction(QIcon(":/png/Tool.png"), AppResources::getUpdateRecordStr(), this);
    update_record_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    connect(update_record_action, SIGNAL(triggered()), this, SLOT(update_record()));

    QAction *add_file_action = new QAction(QIcon(":/png/Add.png"), AppResources::getAddFileStr(), this);
    connect(add_file_action, SIGNAL(triggered()), this, SLOT(add_file()));

    QAction *delete_record_action = new QAction(QIcon(":/png/Delete.png"), AppResources::getDeleteRecordStr(), this);
    connect(delete_record_action, SIGNAL(triggered()), this, SLOT(delete_record()));

    QAction *htmltopdf_action = new QAction(QIcon(":png/Pdf.png"), AppResources::getHtmlToPDF(), this);
    connect(htmltopdf_action, SIGNAL(triggered()), this, SLOT(convert_htmltopdf()));

    QMenu *menu = menubar->addMenu(AppResources::getMenuStr());
    menu->addAction(new_action);
    menu->addAction(open_record_action);
    menu->addAction(update_record_action);
    menu->addAction(delete_record_action);
    menu->addAction(add_file_action);
    menu->addAction(open_file_action);
    menu->addAction(delete_file_action);
    menu->addAction(find_file_duplicate_action);

    QMenu *favorite = menubar->addMenu(AppResources::getFavoritesStr());
    favorite->addAction(open_favorites_action);
    favorite->addAction(add_favorites_action);
    favorite->addAction(delete_favorites_action);
    favorite->addAction(delete_favorites_all_action);

    QMenu *top = menubar->addMenu(AppResources::getTOPStr());
    top->addAction(open_last_view_action);
    top->addAction(open_last_add_action);
    top->addAction(delete_last_view_action);
    top->addAction(delete_last_add_action);

    QMenu *convert = menubar->addMenu(AppResources::getConvert());
    convert->addAction(htmltopdf_action);

    QGroupBox *boxFilter = new QGroupBox(AppResources::getFiltersStr());
    boxFilter->setAlignment(Qt::AlignRight);

    cblTags = new CheckComboboxList();
    cbThemes = new CheckComboBox();
    leAuthor = new CheckLineEdit();
    leAuthor->setCheckBoxText(AppResources::getAuthorStr());
    leName = new CheckLineEdit();
    leName->setCheckBoxText(AppResources::getNameStr());   
    dateFrom = new CheckDatePicker();
    dateFrom->setCheckBoxText(AppResources::getDateFromStr());
    dateTo = new CheckDatePicker();
    dateTo->setCheckBoxText(AppResources::getDateToStr());

    int n = 50;

    QPushButton *squard_add = new QPushButton();
    squard_add->setIcon(QIcon(":/png/Add.png"));
    squard_add->setToolTip(AppResources::getNewRecordStr());
    squard_add->setFixedSize(n, n);
    connect(squard_add, SIGNAL(clicked()), this, SLOT(new_record()));

    QPushButton *squard_open = new QPushButton();
    squard_open->setIcon(QIcon(":/png/Edit Alt.png"));
    squard_open->setToolTip(AppResources::getOpenRecordStr());
    squard_open->setFixedSize(n, n);
    connect(squard_open, SIGNAL(clicked()), this, SLOT(open_record()));

    QPushButton *squard_favorite = new QPushButton();
    squard_favorite->setIcon(QIcon(":/png/Favorites.png"));
    squard_favorite->setToolTip(AppResources::getFavoritesStr());
    squard_favorite->setFixedSize(n, n);
    connect(squard_favorite, SIGNAL(clicked()), this, SLOT(open_favorites()));

    QBoxLayout *layoutButton = new QBoxLayout(QBoxLayout::LeftToRight);
    layoutButton->addWidget(squard_add);
    layoutButton->addWidget(squard_open);
    layoutButton->addWidget(squard_favorite);
    layoutButton->addStretch(1);

    QBoxLayout *layoutBoxFilter = new QBoxLayout(QBoxLayout::Down);
    layoutBoxFilter->addWidget(leName);
    layoutBoxFilter->addWidget(leAuthor);
    layoutBoxFilter->addWidget(cbThemes);
    layoutBoxFilter->addWidget(cblTags);
    layoutBoxFilter->addWidget(dateFrom);
    layoutBoxFilter->addWidget(dateTo);
    boxFilter->setLayout(layoutBoxFilter);

    QGroupBox *boxRecord = new QGroupBox(AppResources::getRecordsStr());
    boxRecord->setAlignment(Qt::AlignRight);

    tableViewRecord = new QTableView();
    tableViewRecord->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewRecord->setSelectionMode(QAbstractItemView::SingleSelection);
    tableViewRecord->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mdlRecords = new QSqlQueryModel();
    tableViewRecord->setModel(mdlRecords);
    connect(tableViewRecord, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(open_record(QModelIndex)));
    connect(tableViewRecord->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(selection_changed(const QItemSelection &)));    

    lTags = new QLabel(AppResources::getTagStr());
    //lTags->setStyleSheet("QLabel { color : darkGreen; }");

    QBoxLayout *layoutBoxRecord = new QBoxLayout(QBoxLayout::Down);
    layoutBoxRecord->addWidget(tableViewRecord);
    layoutBoxRecord->addWidget(lTags);
    boxRecord->setLayout(layoutBoxRecord);

    QGroupBox *boxFile = new QGroupBox(AppResources::getFilesStr());
    boxFile->setAlignment(Qt::AlignRight);

    tableViewFile = new QTableView();
    tableViewFile->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewFile->setSelectionMode(QAbstractItemView::SingleSelection);
    tableViewFile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mdlFiles = new QSqlQueryModel();
    tableViewFile->setModel(mdlFiles);
    connect(tableViewFile, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(open_file(QModelIndex)));

    QBoxLayout *layoutBoxFile = new QBoxLayout(QBoxLayout::Down);
    layoutBoxFile->addWidget(tableViewFile);
    boxFile->setLayout(layoutBoxFile);

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

    traceList = new QListWidget();
    int f_size = traceList->font().pointSize();
    traceList->setFixedHeight(f_size * 6);
    traceList->setSelectionMode(QAbstractItemView::NoSelection);

    QPushButton *pushButtonViewTrace = new QPushButton(QIcon(":/png/Information.png"), "");
    pushButtonViewTrace->setFixedHeight(traceList->height());
    connect(pushButtonViewTrace, SIGNAL(clicked()), this, SLOT(on_pushButtonViewTrace_clicked()));

    QBoxLayout *layoutBottom = new QBoxLayout(QBoxLayout::LeftToRight);
    layoutBottom->addWidget(traceList);
    layoutBottom->addWidget(pushButtonViewTrace);

    tracer = new MyTracer(0, traceList);
    watcher = new Watcher(0, tracer);

    QGridLayout *layoutPgrd  = new QGridLayout();
    layoutPgrd->addWidget(menubar, 0, 0);
    layoutPgrd->addLayout(layoutButton, 1, 0);
    layoutPgrd->addLayout(layoutMain, 2, 0);
    layoutPgrd->addLayout(layoutBottom, 3, 0);

    this->setLayout(layoutPgrd);
    this->setAcceptDrops(true);
    this->setWindowIcon(QIcon(":/Double-J-Design-Ravenna-3d-Book.ico"));

    connect(this, SIGNAL(book_added(int)), this, SLOT(set_newbook(int)));

    int w = 1080;
    int h = 418;
    int s_w = QApplication::desktop()->screen(0)->width();
    int s_h = QApplication::desktop()->screen(0)->height();
    this->setGeometry((s_w - w) / 2, (s_h - h) / 2, w, h);   

    //create app temp folder
    tempPath = QDir::tempPath() + "/ELibrary";
    bool exists = QDir(tempPath).exists();
    if(!exists){
        QDir().mkdir(tempPath);
        tracer->information(tr("Открытие файлов в: ") + tempPath);
    }

    this->checkDB();

    cblTags->init(CheckComboboxList::TAGS);
    cbThemes->init(CheckComboBox::THEMES);
}

int MainWidget::getBookId(){
    int bookid = 0;
    QModelIndexList indexes  = tableViewRecord->selectionModel()->selection().indexes();
    if(indexes.count() > 0) {
        int row = indexes.at(0).row();
        bookid = mdlRecords->record(row).value(0).toInt();
    }
    else {
        tracer->warning(tr("Запись не выбрана"));
    }
    return bookid;
}

int MainWidget::getFileId(){
    int fileid = 0;
    QModelIndexList indexes  = tableViewFile->selectionModel()->selection().indexes();
    if(indexes.count() > 0) {
        int row = indexes.at(0).row();
        fileid = mdlFiles->record(row).value(0).toInt();
    }
    else{
        tracer->warning(tr("Файл не выбран"));
    }
    return fileid;
}

void MainWidget::htmltopdf_finished(QString filename){
    QStringList filenames;
    filenames.append(filename);
    this->add(filenames);
}

void MainWidget::convert_htmltopdf(){
    ConvertWkhtmltopdf *dlgWk = new ConvertWkhtmltopdf(this, tracer, tempPath);
    connect(dlgWk, SIGNAL(finished(QString)), this, SLOT(htmltopdf_finished(QString)));
    dlgWk->setAttribute(Qt::WA_DeleteOnClose);
    dlgWk->show();
}

void MainWidget::add_file(){
    int bookid = this->getBookId();
    if(bookid > 0) {

          QFileDialog *dlgFile = new QFileDialog(this);
          dlgFile->setFileMode(QFileDialog::ExistingFile);
          QString fileName;
          if (dlgFile->exec() == QFileDialog::Accepted)
              fileName = dlgFile->selectedFiles().at(0);
          delete dlgFile;
          if(fileName.isEmpty()) {
              return;
          }
          MngrConnection::Instance().transaction();
          bool _continue = this->checkContinueDuplicate(fileName);
          if(!_continue){
              return;
          }
          tracer->information(tr("Добавление файла... ") + fileName);
          int fileid = MngrQuerys::addFile(bookid, fileName);
          if(fileid > 0){
              MngrQuerys::setFileModel(*mdlFiles, bookid);
              MngrConnection::Instance().commit();
              tableViewFile->setColumnHidden(0, true);
              tracer->OK();

          }
          else if(fileid == -1) {
              MngrConnection::Instance().rollback();
              tracer->critical(tr("Ошибка в открытии файла"));
              return;
          }
          else if(fileid == 0) {
              MngrConnection::Instance().rollback();
              tracer->critical(MngrConnection::Instance().lastError());
              return;
          }
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
    this->add(fileNames);
    event->acceptProposedAction();
}

void MainWidget::open_file(){
    QModelIndexList indexes = tableViewFile->selectionModel()->selection().indexes();
    if(indexes.count() > 0) {
        open_file(indexes.at(0));
    }
    else {
        tracer->warning(tr("Файл не выбран"));
    }
}

void MainWidget::open_record() {
     QModelIndexList indexes  = tableViewRecord->selectionModel()->selection().indexes();
     if(indexes.count() > 0) {
           open_record(indexes.at(0));
     }
     else {
         tracer->warning(tr("Запись не выбрана"));
     }
}

void MainWidget::delete_record(){
    if(!this->checkDB())
        return;
    int bookid = this->getBookId();
    if(bookid > 0) {
          tracer->information(tr("Удаление записи..."));
          MngrConnection::Instance().transaction();
          int result = MngrQuerys::deleteBook(bookid);
          if(result > 0){
              this->reinit_recordtable(QModelIndex());
              MngrConnection::Instance().commit();
              tracer->OK();
          } else {
              MngrConnection::Instance().rollback();
              tracer->critical(MngrConnection::Instance().lastError());
          }
    }
}

void MainWidget::find_file_duplicate(){
    QFileDialog *dlgFile = new QFileDialog(this);
    dlgFile->setFileMode(QFileDialog::ExistingFile);
    QString fileName;
    if (dlgFile->exec() == QFileDialog::Accepted)
        fileName = dlgFile->selectedFiles().at(0);
    delete dlgFile;
    if(fileName.isEmpty()) {
        return;
    }
    QString inf;
    MngrConnection::Instance().transaction();
    bool duplicate = this->checkFileDuplicate(fileName, inf);
    MngrConnection::Instance().commit();
    if(duplicate){
        tracer->warning(tr("Файл присутствует в БД"));
        tracer->warning(inf);
    } else {
        tracer->information(tr("Файл в БД не найден"));
        tracer->OK();
    }
}

bool MainWidget::checkFileDuplicate(QString fileName, QString &out_inf){
    bool duplicate = false;
    int fileId = MngrQuerys::findFileDuplicate(fileName, out_inf);
    if(fileId > 0)
        duplicate = true;
    else if(fileId == -2)
        tracer->critical(tr("Ошибка в открытии файла"));
    else if(fileId == 0)
        tracer->critical(MngrConnection::Instance().lastError());
    return duplicate;
}

void MainWidget::open_file(QModelIndex index){
    if(!this->checkDB())
        return;
    int row = index.row();
    int fileid = mdlFiles->record(row).value(0).toInt();
    ObjFile objFile;
    tracer->information(tr("Получение файла..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::getFile(fileid, objFile);
    MngrConnection::Instance().commit();
    tracer->OK();
    QString path = tempPath + '/' + objFile.getName();
    objFile.setPath(path);
    if(!objFile.getArray().isEmpty()) {
        if(!QFile::exists(path)){
            tracer->information(tr("Создание файла... ") +
                                objFile.getName());
            QFile file(path);
            file.open(QIODevice::WriteOnly);
            file.write(objFile.getArray());
            file.close();
            tracer->OK();
            tracer->information(tr("Добавление в отслеживаемый список... ") +
                                objFile.getName());
            watcher->addFile(objFile);
            tracer->OK();
        }
        else {
            tracer->warning(tr("В директории назначения файл уже существует ") +
                            objFile.getName());
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
    else{
        tracer->critical(tr("Ошибка в открытии файла"));
    }
}

void MainWidget::open_record(QModelIndex index){
    if(!this->checkDB())
        return;
    int row = index.row();
    int bookid = mdlRecords->record(row).value(0).toInt();
    QList<ObjFile*> files;
    tracer->information(tr("Получение файлов..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::getFiles(bookid, files);
    MngrConnection::Instance().commit();
    tracer->OK();
    if(files.count() > 0) {
        for(int i(0); i < files.count(); ++i){
            QString path = tempPath + '/' + files.at(i)->getName();
            files.at(i)->setPath(path);
            if(!QFile::exists(path)) {
                tracer->information(tr("Создание файла... ") +
                                    files.at(i)->getName());
                QFile file(path);
                file.open(QIODevice::WriteOnly);
                file.write(files.at(i)->getArray());
                file.close();
                tracer->OK();
                tracer->information(tr("Добавление в отслеживаемый список... ") +
                                    files.at(i)->getName());
                watcher->addFile(files.at(i));
                tracer->OK();
            }
            else{
                tracer->warning(tr("В директории назначения файл уже существует ") +
                                files.at(i)->getName());
            }
            delete files.at(i);
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(tempPath));
        if(AppSettings::Instance().getIsLog()){
            tracer->information(tr("Логирование..."));
            MngrConnection::Instance().transaction();
            int usersBookId = MngrQuerys::addLastViewBook(bookid);
            if(usersBookId == 0) {
                tracer->critical(MngrConnection::Instance().lastError());
            }
            MngrConnection::Instance().commit();
            tracer->OK();
        }
    }
    else {
        tracer->critical(tr("Ошибка в открытии файлов"));
    }
}

void MainWidget::update_record(){
    if(!this->checkDB())
        return;
    QModelIndexList indexes  = tableViewRecord->selectionModel()->selection().indexes();
    if(indexes.count() > 0) {
        QModelIndex index = indexes.at(0);
        int row = index.row();
        ObjRecord record(mdlRecords->record(row).value(3).toString(),
                         mdlRecords->record(row).value(4).toString(),
                         mdlRecords->record(row).value(5).toString(),
                         mdlRecords->record(row).value(6).toString(),
                         lTags->text().split(','),
                         mdlRecords->record(row).value(0).toInt());


        MngrConnection::Instance().transaction();
        QStringList themes = MngrQuerys::getThemes();
        QStringList tags = MngrQuerys::getTags();
        MngrConnection::Instance().commit();

        BookDialog *dlgBook = new BookDialog(this);
        dlgBook->setRecord(record);
        dlgBook->setThemes(themes);
        dlgBook->setTags(tags);
        dlgBook->setHiddenAddFilesButton(true);
        if(dlgBook->exec() == QDialog::Accepted){
            dlgBook->updateRecord(record);
            delete dlgBook;
            tracer->information(tr("Обновление информации о записи..."));
            MngrConnection::Instance().transaction();
            int r_book = MngrQuerys::updateBook(record);
            if(r_book > 0){
                tracer->OK();
                tracer->information(tr("Перепривязка тэгов..."));
                int r_tag = MngrQuerys::deleteTags(record.getId());
                if(r_tag > 0){
                    int bookid = record.getId();
                    QStringList v_tags = record.getTags();
                    for(int i(0); i < v_tags.count(); ++i) {
                        int tagId = MngrQuerys::addTag(bookid, v_tags.at(i));
                        if(tagId == 0) {
                            MngrConnection::Instance().rollback();
                            tracer->critical(MngrConnection::Instance().lastError());
                            return;
                        }
                    }
                    this->reinit_recordtable(index);
                    MngrConnection::Instance().commit();                                
                    tracer->OK();

                }
                else {
                    MngrConnection::Instance().rollback();
                    tracer->critical(MngrConnection::Instance().lastError());
                }
            }
            else {
                MngrConnection::Instance().rollback();
                tracer->critical(MngrConnection::Instance().lastError());
            }
        }
        else
            delete dlgBook;
    }
    else {
        tracer->warning(tr("Запись не выбрана"));
    }
}

void MainWidget::reinit_recordtable(QModelIndex index){
    //reinit select
    QVariant name = leName->getValue();
    QVariant author = leAuthor->getValue();
    QVariant theme = cbThemes->getValue();
    QVariant datefrom = dateFrom->getValue();
    QVariant dateto = dateTo->getValue();
    QVariant flagtag = cblTags->getFlag();
    MngrQuerys::setRecordModel(*mdlRecords, name, author, theme, datefrom, dateto, flagtag);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    tableViewFile->setColumnHidden(0, true);
    tableViewRecord->setColumnHidden(0, true);
    tableViewRecord->selectionModel()->select(index, QItemSelectionModel::Select);
}

bool MainWidget::checkDB(){
    if(!MngrConnection::Instance().isOpen()){
        if(!MngrConnection::Instance().open()) {
            tracer->critical(MngrConnection::Instance().lastError());
            return false;
        }
    }
    return true;
}

void MainWidget::open_last_view(){
    if(!this->checkDB())
        return;
    tracer->information(tr("Последние открытые записи..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::setRecordModelLastView(*mdlRecords);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    MngrConnection::Instance().commit();
    tracer->OK();
    tableViewRecord->setColumnHidden(0, true);
}

void MainWidget::open_last_add(){
    if(!this->checkDB())
        return;
    tracer->information(tr("Последние добавленные записи..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::setRecordModelLastAdd(*mdlRecords);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    MngrConnection::Instance().commit();
    tracer->OK();
    tableViewRecord->setColumnHidden(0, true);
}

void MainWidget::delete_last_view(){
    if(!this->checkDB())
        return;
    tracer->information(tr("Удаление списка последних открытых записей..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::deleteLastViewBooks();
    MngrQuerys::setRecordModelLastView(*mdlRecords);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    MngrConnection::Instance().commit();
    tracer->OK();
    tableViewRecord->setColumnHidden(0, true);
    tableViewFile->setColumnHidden(0, true);
}

void MainWidget::delete_last_add(){
    if(!this->checkDB())
        return;
    tracer->information(tr("Удаление списка последних добавленных записей..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::deleteLastAddBooks();
    MngrQuerys::setRecordModelLastAdd(*mdlRecords);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    MngrConnection::Instance().commit();
    tracer->OK();
    tableViewRecord->setColumnHidden(0, true);
    tableViewFile->setColumnHidden(0, true);
}

void MainWidget::add_favorites(){
    if(!this->checkDB())
        return;
    int bookid = this->getBookId();
    if(bookid == 0) {
        return;
    }
    tracer->information(tr("Добавление в \"Избранное\"..."));
    MngrConnection::Instance().transaction();
    int result = MngrQuerys::addFavoriteBook(bookid);
    MngrConnection::Instance().commit();
    if(result > 0) {
        tracer->OK();
    }
    else if (result == -1){
        tracer->warning(tr("Запись уже присутствует в \"Избранное\""));
    } else if(result == 0) {
        tracer->critical(MngrConnection::Instance().lastError());
    }
}

void MainWidget::open_favorites(){
    if(!this->checkDB())
        return;
    tracer->information(tr("\"Избранное\"..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::setRecordModelFavorites(*mdlRecords);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    MngrConnection::Instance().commit();
    tracer->OK();
    tableViewRecord->setColumnHidden(0, true);
}

void MainWidget::delete_favorites(){
    if(!this->checkDB())
        return;
    int bookid = this->getBookId();
    if(bookid == 0) {
        return;
    }    
    tracer->information(tr("Удаление записи из \"Избранное\"..."));
    MngrConnection::Instance().transaction();
    int result = MngrQuerys::deleteFavoritesBook(bookid);    
    if(result > 0) {
        MngrQuerys::setRecordModelFavorites(*mdlRecords);
        MngrQuerys::setFileModel(*mdlFiles, 0);
        tracer->OK();
    }
    else if(result == -1) {
       tracer->warning(tr("Запись не присутствует в \"Избранное\""));
    } else if (result == 0) {
       tracer->critical(MngrConnection::Instance().lastError());
    }
    MngrConnection::Instance().commit();

}

void MainWidget::delete_favorites_all(){
    if(!this->checkDB())
        return;
    tracer->information(tr("Удаление списка \"Избранное\"..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::deleteFavoritesBooks();
    MngrQuerys::setRecordModelFavorites(*mdlRecords);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    MngrConnection::Instance().commit();
    tracer->OK();
    tableViewRecord->setColumnHidden(0, true);
    tableViewFile->setColumnHidden(0, true);
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
    lTags->setText(text);
    MngrConnection::Instance().transaction();
    MngrQuerys::setFileModel(*mdlFiles, bookid);
    MngrConnection::Instance().commit();
    tableViewFile->setColumnHidden(0, true);
}

void MainWidget::on_pushButtonFind_clicked(){
    if(!this->checkDB())
        return;
    QVariant name = leName->getValue();
    QVariant author = leAuthor->getValue();
    QVariant theme = cbThemes->getValue();
    QVariant datefrom = dateFrom->getValue();
    QVariant dateto = dateTo->getValue();
    QVariant flagtag = cblTags->getFlag();
    tracer->information(tr("Выборка..."));
    MngrConnection::Instance().transaction();
    MngrQuerys::setRecordModel(*mdlRecords, name, author, theme, datefrom, dateto, flagtag);
    MngrQuerys::setFileModel(*mdlFiles, 0);
    MngrConnection::Instance().commit();
    tracer->OK();
    tableViewRecord->setColumnHidden(0, true);
    tableViewFile->setColumnHidden(0, true);
}

void MainWidget::on_pushButtonViewTrace_clicked(){
    ViewListWidget *widget = new ViewListWidget(this, traceList);    
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->show();
    widget->scrollToBottom();
}

void MainWidget::delete_file(){
    if(!this->checkDB())
        return;
    int fileid = this->getFileId();
    if(fileid > 0) {
        tracer->information(tr("Удаление файла... "));
        MngrConnection::Instance().transaction();
        int result = MngrQuerys::deleteFile(fileid);
        if(result > 0){
            int bookid = this->getBookId();
            if(bookid > 0){
               MngrQuerys::setFileModel(*mdlFiles, bookid);
               tableViewFile->setColumnHidden(0, true);
            }
            MngrConnection::Instance().commit();
            tracer->OK();
        }
        else {
            MngrConnection::Instance().rollback();
            tracer->critical(MngrConnection::Instance().lastError());
        }
    }
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
    this->add(fileNames);
}

void MainWidget::add(QStringList fileNames){
    MngrConnection::Instance().transaction();
    QStringList themes = MngrQuerys::getThemes();
    QStringList tags = MngrQuerys::getTags();
    MngrConnection::Instance().commit();

    BookDialog *dlgBook = new BookDialog(this);
    dlgBook->setName(fileNames.at(0));
    dlgBook->setThemes(themes);
    dlgBook->setTags(tags);
    if(dlgBook->exec() == QDialog::Accepted) {
        QStringList addFileNames = dlgBook->getFileNames();
        for(int i(0); i < addFileNames.count(); ++i) {
             fileNames.append(addFileNames.at(i));
        }
        ObjRecord record = dlgBook->getRecord();
        delete dlgBook;

        MngrConnection::Instance().transaction();
        for(int i(0); i < fileNames.count(); ++i){         
           bool _continue = this->checkContinueDuplicate(fileNames.at(i));
           if(!_continue){
               return;
           }
        }
        MngrConnection::Instance().commit();

        this->addRecordAsync(fileNames, record);
    }
    else
        delete dlgBook;

}

bool MainWidget::checkContinueDuplicate(QString fileName){
    bool _continue = true;
    QString inf;
    bool duplicate = this->checkFileDuplicate(fileName, inf);
    if(duplicate){
        QMessageBox msgBox;
        QString text = tr("Файл найден в БД\n") + inf;
        msgBox.setText(text);
        msgBox.setInformativeText(tr("Продолжить добавление записи?"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Cancel){
            MngrConnection::Instance().commit();
            _continue = false;
        }
    }
    return _continue;
}

void MainWidget::addRecord(QStringList &fileNames, ObjRecord &record){
    QStringList tags = record.getTags();
    if(MngrConnection::Instance().transaction()) {
        tracer->information_invoke(tr("Добавление информации о записи..."));
        int bookId = MngrQuerys::addBook(record);
        record.setId(bookId);
        if(bookId > 0) {
            tracer->OK_invoke();
            tracer->information_invoke(tr("Добавление файлов..."));
            for(int i(0); i < fileNames.count(); ++i) {
                int fileId = MngrQuerys::addFile(bookId, fileNames.at(i));
                if(fileId == -1) {
                    MngrConnection::Instance().rollback();
                    tracer->critical_invoke(tr("Ошибка в открытии файла"));                    
                    return;
                }
                else if(fileId == 0) {
                    MngrConnection::Instance().rollback();
                    tracer->critical_invoke(MngrConnection::Instance().lastError());                    
                    return;
                }
            }
            tracer->OK_invoke();
            tracer->information_invoke(tr("Привязка тэгов..."));
            for(int i(0); i < tags.count(); ++i) {
                int tagId = MngrQuerys::addTag(bookId, tags.at(i));
                if(tagId == 0) {
                    MngrConnection::Instance().rollback();
                    tracer->critical_invoke(MngrConnection::Instance().lastError());                    
                    return;
                }
            }
            tracer->OK_invoke();
            if(AppSettings::Instance().getIsLog()){
                tracer->information_invoke(tr("Логирование..."));
                int usersBookId = MngrQuerys::addLastAddBook(bookId);
                if(usersBookId == 0) {
                    tracer->critical_invoke(MngrConnection::Instance().lastError());
                }
                tracer->OK_invoke();
            }
            MngrConnection::Instance().commit();
            tracer->information_invoke(tr("Запись добавлена"));
            emit book_added(bookId);
            cbThemes->init(CheckComboBox::THEMES);
            cblTags->init(CheckComboboxList::TAGS);            
        }
        else if (bookId == 0) {
            MngrConnection::Instance().rollback();
            tracer->critical_invoke(MngrConnection::Instance().lastError());
        }
    }
    else
        tracer->critical_invoke(MngrConnection::Instance().lastError());    
}

void MainWidget::addRecordAsync(QStringList &fileNames, ObjRecord &record){
    QtConcurrent::run(this, &MainWidget::addRecord, fileNames, record);
}

void MainWidget::set_newbook(int bookid){
    MngrConnection::Instance().transaction();
    MngrQuerys::setRecordModelNewBook(*mdlRecords, bookid);
    MngrQuerys::setRecordModelNewBook(*mdlFiles, bookid);
    MngrConnection::Instance().commit();
    tableViewRecord->setColumnHidden(0, true);
    tableViewFile->setColumnHidden(0, true);
}

void MainWidget::closeEvent(QCloseEvent *event) {   
    dateFrom->closeCalendar();
    dateTo->closeCalendar();
    watcher->stopWatching();
    MngrConnection::Instance().close();
    FileUtils::removeDir(tempPath);
    event->accept();
}

MainWidget::~MainWidget() {    
    delete tracer;
    delete watcher;
}
