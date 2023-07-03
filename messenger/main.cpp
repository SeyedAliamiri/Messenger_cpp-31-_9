#include "mainwindow.h"
#include<QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir* dir=new QDir(QDir::currentPath()+"/users");
    if(!dir->exists()){
        QDir* dir_u=new QDir(QDir::currentPath());
        dir_u->mkdir("users");
        delete dir_u;
    }
    delete dir;
    QDir* dir2=new QDir(QDir::currentPath()+"/channels");
    if(!dir2->exists()){
        QDir* dir_c=new QDir(QDir::currentPath());
        dir_c->mkdir("channels");
        delete dir_c;

    }
    delete dir2;
    QDir* dir3=new QDir(QDir::currentPath()+"/groups");
    if(!dir3->exists()){
        QDir* dir_g=new QDir(QDir::currentPath());
        dir_g->mkdir("groups");
        delete dir_g;

    }
    delete dir3;
    MainWindow w;
    w.setWindowIcon(QIcon(":/new/prefix1/appicon.png"));
    w.setWindowTitle("messenger");
    w.first_check();
    return a.exec();
}
