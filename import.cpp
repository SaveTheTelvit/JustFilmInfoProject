#include "import.h"
#include "ui_import.h"

Import::Import(QWidget *parent, DataBase *db)
    : QWidget(parent)
    , ui(new Ui::Import)
    , db(db)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &Import::currentIndexChanged);
    connect(ui->listWidget, &QListWidget::itemActivated, this, [](QListWidgetItem* item)
    {if (item->checkState() == Qt::Unchecked) {item->setCheckState(Qt::Checked);} else item->setCheckState(Qt::Unchecked);});
}
Import::~Import()
{
    delete ui;
}

void Import::findImportFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Импорт данных"), "/home" ,tr("fill(*.fill)"));
    films.clear();
    ui->listWidget->clear();
    if (filePath != "") {
        readImportFile(filePath);
        std::sort(films.begin(), films.end(),
                  [](const FilmInfo& film1, const FilmInfo& film2){return film1.name < film2.name;});
        for (int i = 0; i < films.size(); ++i) {
            QListWidgetItem *item = new QListWidgetItem(films[i].name, ui->listWidget);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
        ui->listWidget->setCurrentRow(0);
        emit toImport();
    } else {
        emit toMain();
    }
}

void Import::on_pushButton_clicked()
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            qDebug() << QString("Элемент %1 отмечен " + item->text()).arg(i+1);
            if (!db->importFilmData(films[ui->listWidget->row(item)])) {
                qDebug() << "Фильм с таким названием уже существует";
            }
        }
    }
}

void Import::currentIndexChanged()
{
    int index = ui->listWidget->currentRow();
    QVector<QString> strings;
    if (index >= 0 && index < films.size()) {
        FilmInfo film = films[index];
        strings << ("Name: " + film.name) << ("Format: " + film.format.toStr()) << ("Duration: " + film.duration.toStr())
                << ("TitleTime: " + film.titleTime.toStr()) << ("Volume: " + film.volume.toStr());
        for (int i = 0; i < film.tlrs.size(); ++i) {
            strings << ("Tlr " + QString::number(i + 1) + ":");
            strings << ("Name: " + film.tlrs[i].name) << ("Duration: " + film.tlrs[i].duration.toStr())
                    << ("Volume: " + film.tlrs[i].volume.toStr());
        }
    }
    for (int i = 0; i < strings.size(); ++i) {
        qDebug() << strings[i];
    }
}


void Import::readImportFile(const QString& fileName)
{
    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    QXmlStreamReader xml(file);
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
          if (xml.name().toString() == "FilmInfo") {
              films.push_back(readFilmInfo(xml));
          }
        }
    }
}

FilmInfo Import::readFilmInfo(QXmlStreamReader &xml)
{
    FilmInfo film;
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            QString name = xml.name().toString();
            if (name == "Name") {
                film.name = xml.readElementText();
            } else if (name == "Format") {
                film.format = xml.readElementText().toInt();
            } else if (name == "Duration") {
                film.duration = FTime(xml.readElementText());
            } else if (name == "TitleTime") {
                film.titleTime = FTime(xml.readElementText());
            } else if (name == "Volume") {
                film.volume = Volume(xml.readElementText());
            } else if (name == "TlrInfo") {
                film.tlrs.push_back(readTlrInfo(xml));
            }
        } else if (token == QXmlStreamReader::EndElement && xml.name().toString() == "FilmInfo") {
            return film;
        }
    }
    return film;
}

TlrInfo Import::readTlrInfo(QXmlStreamReader &xml)
{
    TlrInfo tlr;
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            QString name = xml.name().toString();
            if (name == "Name") {
                tlr.name = xml.readElementText();
            } else if (name == "Duration") {
                tlr.duration = FTime(xml.readElementText());
            } if (name == "Volume") {
                tlr.volume = Volume(xml.readElementText());
            }
        } else if (token == QXmlStreamReader::EndElement && xml.name().toString() == "TlrInfo") {
            return tlr;
        }
    }
    return tlr;
}
