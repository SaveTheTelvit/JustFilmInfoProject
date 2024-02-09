#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DataBase;
    db->openDataBase();
    setupMenu();

    filmView = new FilmView(this, db);
    import = new Import(this, db);
    ui->stackedWidget->addWidget(filmView);
    ui->stackedWidget->addWidget(import);
    connect(import, &Import::toMain, this, [this](){ui->stackedWidget->setCurrentWidget(filmView); filmView->setupFilms();});
    connect(import, &Import::toImport, this, [this](){ui->stackedWidget->setCurrentWidget(import);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu()
{
    QAction *importData = new QAction("Импорировать данные", this);
    QAction *exportData = new QAction("Экспортитровать данные", this);
    QAction *exit = new QAction("Выход", this);
    ui->menu->addAction(importData);
    ui->menu->addAction(exportData);
    ui->menu->addSeparator();
    ui->menu->addAction(exit);
    connect(importData, &QAction::triggered, this, &MainWindow::importData);
    connect(exportData, &QAction::triggered, this, &MainWindow::exportData);
    connect(exit, &QAction::triggered, this, &QApplication::quit);
}

void MainWindow::importData()
{
    import->findImportFile();
}

void MainWindow::exportData()
{
    qDebug() << "export";
}
