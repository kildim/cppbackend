// Возьмите решение предыдущей задачи
// о фотоальбоме в качестве заготовки.
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
