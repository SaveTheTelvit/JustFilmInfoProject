#include "database.h"

void DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("TestData.db");
    if (!db.open()) {
        qDebug() << "No opened.";
  } else {
        qDebug() << "Open!";
        QSqlQuery("PRAGMA foreign_keys = ON").exec();
        if (!db.tables(QSql::AllTables).contains("FILMS")) createTables();
  }
}

void DataBase::createTables()
{
    createFilmsTable();
    createTlrsTable();
    createFilmTlrTable();
}

bool DataBase::createFilmsTable()
{
    if (!db.tables(QSql::AllTables).contains("FILMS")) {
    QSqlQuery query("CREATE TABLE FILMS ("
                    "id INTEGER,"
                    "name TEXT NOT NULL,"
                    "format INTEGER,"
                    "duration INTEGER,"
                    "titleTime INTEGER,"
                    "volume INTEGER,"
                    "PRIMARY KEY (id AUTOINCREMENT)"
                    ")");
    return !query.exec();
    } else return 1;
}

bool DataBase::createTlrsTable()
{
    if (!db.tables(QSql::AllTables).contains("TLRS")) {
        QSqlQuery query("CREATE TABLE TLRS ("
                        "id INTEGER,"
                        "name TEXT NOT NULL,"
                        "duration INTEGER,"
                        "volume INTEGER,"
                        "PRIMARY KEY (id AUTOINCREMENT)"
                        ")");
        return !query.exec();
    } else return 1;
}

bool DataBase::createFilmTlrTable()
{
    if (!db.tables(QSql::AllTables).contains("FILM_TLR")) {
        QSqlQuery query("CREATE TABLE FILM_TLR ("
                        "film_id INTEGER,"
                        "video_pos INTEGER,"
                        "tlr_id INTEGER,"
                        "PRIMARY KEY (film_id, video_pos),"
                        "FOREIGN KEY (film_id) REFERENCES FILMS(id) ON UPDATE CASCADE ON DELETE CASCADE,"
                        "FOREIGN KEY (tlr_id) REFERENCES TLRS(id) ON UPDATE CASCADE ON DELETE CASCADE"
                        ")");
        return !query.exec();
    } else return 1;
}

int DataBase::insertIntoFilms(const QVariantList& data)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM FILMS WHERE name = :name AND "
                  "format = :format AND duration = :duration AND titleTime = :titleTime AND volume = :volume");
    query.bindValue(":name", data[0].toString());
    query.bindValue(":format", data[1].toInt());
    query.bindValue(":duration", data[2].toInt());
    query.bindValue(":titleTime", data[3].toInt());
    query.bindValue(":volume", data[4].toInt());
    query.exec();
    if (!query.first()) {
        query.prepare("INSERT INTO FILMS VALUES (NULL, :name, :format, :duration, :titleTime, :volume)");
        query.bindValue(":name", data[0].toString());
        query.bindValue(":format", data[1].toInt());
        query.bindValue(":duration", data[2].toInt());
        query.bindValue(":titleTime", data[3].toInt());
        query.bindValue(":volume", data[4].toInt());
        query.exec();
        query.exec("SELECT last_insert_rowid()");
        if (query.first()) return query.value(0).toInt();
    }
    return -1;
}

int DataBase::insertIntoTlrs(const QVariantList& data)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM TLRS WHERE name = :name AND "
                  "duration = :duration AND volume = :volume");
    query.bindValue(":name", data[0].toString());
    query.bindValue(":duration", data[1].toInt());
    query.bindValue(":volume", data[2].toInt());
    query.exec();
    if (!query.first()) {
        query.prepare("INSERT INTO TLRS VALUES (NULL, :name, :duration, :volume)");
        query.bindValue(":name", data[0].toString());
        query.bindValue(":duration", data[1].toInt());
        query.bindValue(":volume", data[2].toInt());
        query.exec();
        query.exec("SELECT last_insert_rowid()");
        if (query.first()) return query.value(0).toInt();
        return -1;
    }
    return query.value(0).toInt();
}

void DataBase::insertIntoFilmTlr(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FILM_TLR VALUES (:film_id, :pos, :tlr_id)");
    query.bindValue(":film_id", data[0].toInt());
    query.bindValue(":pos", data[1].toInt());
    query.bindValue(":tlr_id", data[2].toInt());
    query.exec();
}

bool DataBase::importFilmData(const FilmInfo& film)
{
    QVariantList filmData;
    filmData.append(film.name);
    filmData.append(film.format.toInt());
    filmData.append(film.duration.duration());
    filmData.append(film.titleTime.duration());
    filmData.append(film.volume.toInt());
    int filmID = insertIntoFilms(filmData);
    if (filmID != -1) {
        for (int j = 0; j < film.tlrs.size(); ++j) {
            QVariantList tlrInfo;
            tlrInfo.append(film.tlrs[j].name);
            tlrInfo.append(film.tlrs[j].duration.duration());
            tlrInfo.append(film.tlrs[j].volume.toInt());
            int tlrID = insertIntoTlrs(tlrInfo);
            QVariantList filmTlr;
            filmTlr << filmID << j << tlrID;
            insertIntoFilmTlr(filmTlr);
        }
        return true;
    } else return false;
}
