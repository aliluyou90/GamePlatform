#include "mainwindow.h"
#include <QApplication>
MainWindow * mainwindow;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow = new MainWindow();
    mainwindow->show();


    return a.exec();
}
