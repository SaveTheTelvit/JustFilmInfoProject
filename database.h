#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

#include "structs.h"

class DataBase
{
public:
    void openDataBase();
    void createTables();
    int insertIntoFilms(const QVariantList& data);
    int insertIntoTlrs(const QVariantList& data);
    void insertIntoFilmTlr(const QVariantList& data);
    bool importFilmData(const FilmInfo& film);

private:
    bool createFilmsTable();
    bool createTlrsTable();
    bool createFilmTlrTable();
    QSqlDatabase db;
};

#endif // DATABASE_H

