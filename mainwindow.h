#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QShowEvent>

#include "database.h"
#include "import.h"
#include "filmview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void importData();
    void exportData();
    void setupMenu();
    Import *import;
    FilmView *filmView;
    Ui::MainWindow *ui;
    DataBase *db;
};
#endif // MAINWINDOW_H
