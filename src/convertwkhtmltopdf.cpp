#include "convertwkhtmltopdf.h"

ConvertWkhtmltopdf::ConvertWkhtmltopdf(QWidget *parent, MyTracer *tracer, QString tempPath) :
    QDialog(parent)
{
    this->tempPath = tempPath;
    this->tracer = tracer;
    this->process = 0;

    QLabel *nameLabel = new QLabel(AppResources::getNameStr());

    nameLineEdit = new QLineEdit();
    nameLineEdit->setText(".pdf");

    QBoxLayout *nameLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    nameLayout->addWidget(nameLabel, 1);
    nameLayout->addWidget(nameLineEdit, 2);

    QLabel *urlLabel = new QLabel(AppResources::getURLStr());

    urlLineEdit = new QLineEdit();

    QBoxLayout *urlLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    urlLayout->addWidget(urlLabel, 1);
    urlLayout->addWidget(urlLineEdit, 2);

    QPushButton *buttonAddUrl = new QPushButton(tr("+"));
    connect(buttonAddUrl, SIGNAL(clicked()), this, SLOT(on_buttonAddUrl_clicked()));

    QPushButton *buttonDeleteUrl = new QPushButton(tr("-"));
    connect(buttonDeleteUrl, SIGNAL(clicked()), this, SLOT(on_buttonDeleteUrl_clicked()));

    QBoxLayout *buttonLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    buttonLayout->addWidget(buttonAddUrl);
    buttonLayout->addWidget(buttonDeleteUrl);

    urlsList = new QListWidget();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(on_accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(on_reject()));

    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::Down);
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(urlLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(urlsList);
    mainLayout->addWidget(buttonBox);

    this->setLayout(mainLayout);
}

void ConvertWkhtmltopdf::ready_read_output(){
    if(tracer == 0){
        return;
    }

    QByteArray byteArray = process->readAllStandardOutput();
    QStringList strLines = QString(byteArray).split("\n");

    foreach (QString line, strLines){
        if(line != "\r" && !line.isEmpty()){
            tracer->information(line);
        }
    }
}

void ConvertWkhtmltopdf::ready_read_error(){
    if(tracer == 0){
        return;
    }

    QByteArray byteArray = process->readAllStandardError();
    QStringList strLines = QString(byteArray).split("\n");

    foreach (QString line, strLines){
        if(line != "\r" && !line.isEmpty()){
            tracer->critical(line);
        }
    }
}

void ConvertWkhtmltopdf::finished_process(int exitCode){
    if(exitCode == QProcess::NormalExit){
        QString filename = tempPath + '/' + nameLineEdit->text();
        emit finished(filename);
    }
    this->close();
}

void ConvertWkhtmltopdf::on_accept(){
    if(process != 0 && process->isOpen()){
        return;
    }

    QString app_dir = QApplication::applicationDirPath();
    QString program = app_dir + "/wkhtmltopdf/wkhtmltopdf";

    QStringList arg = this->getArguments();

    process  = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);

    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(ready_read_output()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(ready_read_error()));
    connect(process, SIGNAL(finished(int)), this, SLOT(finished_process(int)));

    process->start(program, arg);

    QListWidgetItem * item = new QListWidgetItem(urlsList);
    item->setText(AppResources::getProcessStart());
    item->setTextColor(Qt::green);

    urlsList->addItem(item);
}

void ConvertWkhtmltopdf::on_reject(){
    this->close();
}

void ConvertWkhtmltopdf::on_buttonAddUrl_clicked(){
    QString url = urlLineEdit->text();
    urlsList->addItem(url);
}

void ConvertWkhtmltopdf::on_buttonDeleteUrl_clicked(){
    int row = urlsList->row(urlsList->currentItem());
    urlsList->takeItem(row);
}

QStringList ConvertWkhtmltopdf::getArguments(){
    QStringList arg;  
    arg.append("--footer-center");
    arg.append("[page]");
    arg.append("-s");
    arg.append("Letter");

    for(int i(0); i < urlsList->count(); ++i){
        arg.append(urlsList->item(i)->text());
    }    
    arg.append(tempPath + '/' + nameLineEdit->text());
    return arg;
}

ConvertWkhtmltopdf::~ConvertWkhtmltopdf(){
    if(process != 0)
        delete process;
}
