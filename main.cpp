#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(0, 0, QApplication::primaryScreen()->geometry().width() * 2 / 7, QApplication::primaryScreen()->geometry().height());
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
