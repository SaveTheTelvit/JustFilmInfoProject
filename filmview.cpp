#include "filmview.h"
#include "ui_filmview.h"

FilmView::FilmView(QWidget *parent, DataBase *db)
    : QWidget(parent)
    , ui(new Ui::FilmView)
    , db(db)
{
    ui->setupUi(this);
    setupFilms();
    connect(ui->Films, &QListWidget::currentItemChanged, this, &FilmView::test);
}

FilmView::~FilmView()
{
    delete ui;
}

void FilmView::test()
{
    qDebug() << films[ui->Films->currentRow()].id;
}

void FilmView::setupFilms()
{
    films.clear();
    ui->Films->clear();
    QSqlQuery query("SELECT * FROM FILMS ORDER BY name");
    for (int i = 0; query.next(); ++i) {
        FilmInfo film;
        film.id = query.value(0).toInt();
        film.name = query.value(1).toString();
        film.format = query.value(2).toInt();
        film.duration = query.value(3).toInt();
        film.titleTime = query.value(4).toInt();
        film.volume = query.value(5).toInt();
        QSqlQuery tlrsQuery("SELECT TLRS.name, TLRS.duration, TLRS.volume FROM TLRS "
                   "JOIN FILM_TLR ON TLRS.id = FILM_TLR.tlr_id "
                   "WHERE FILM_TLR.film_id = 1 ORDER BY video_pos");
        for (int j = 0; !tlrsQuery.next(); ++j) {
            TlrInfo tlr;
            tlr.name = tlrsQuery.value(0).toString();
            tlr.duration = tlrsQuery.value(1).toInt();
            tlr.volume = tlrsQuery.value(2).toInt();
            film.tlrs.push_back(tlr);
        }
        films.insert(i, film);
        new QListWidgetItem(film.name, ui->Films);
    }
}
