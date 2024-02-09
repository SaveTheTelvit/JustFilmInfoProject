#ifndef FILMVIEW_H
#define FILMVIEW_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QMap>

#include "database.h"
#include "structs.h"

namespace Ui {
    class FilmView;
}

class FilmView : public QWidget
{
    Q_OBJECT

public:
    explicit FilmView(QWidget *parent = nullptr, DataBase *db = nullptr);
    ~FilmView();
     void setupFilms();
private:
    void test();
    Ui::FilmView *ui;
    DataBase *db;
    QMap<int, FilmInfo> films;
};

#endif // FILMVIEW_H
