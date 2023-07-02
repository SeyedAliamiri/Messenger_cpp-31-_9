#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/new/prefix1/appicon.png"));
    w.setWindowTitle("messenger");
    w.first_check();
    return a.exec();
}
