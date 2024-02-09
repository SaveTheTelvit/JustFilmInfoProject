#ifndef IMPORT_H
#define IMPORT_H

#include <algorithm>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <QXmlStreamReader>

#include "database.h"
#include "structs.h"

namespace Ui {
class Import;
}

class Import : public QWidget
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = nullptr, DataBase *db = nullptr);
    ~Import();
    void findImportFile();

signals:
    void toMain();
    void toImport();

private slots:
    void on_pushButton_clicked();
    void currentIndexChanged();

private:
    void readImportFile(const QString& fileName);
    FilmInfo readFilmInfo(QXmlStreamReader& xml);
    TlrInfo readTlrInfo(QXmlStreamReader& xml);
    Ui::Import *ui;
    QString importFile;
    QVector<FilmInfo> films;
    DataBase *db;
};

#endif // IMPORT_H
