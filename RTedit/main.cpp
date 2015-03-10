#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <QtPlugin>
#include <QLibrary>


int main(int argc, char *argv[]){
    QCoreApplication::addLibraryPath("plugins");
    QApplication a(argc, argv);
    qDebug() << a.libraryPaths();
    MainWindow w;
    w.show();

    return a.exec();
}
