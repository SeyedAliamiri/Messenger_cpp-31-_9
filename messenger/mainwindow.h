#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "log_in.h"
#include "sign_in.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void signup(QString username, QString password, QString firstname, QString lastname);
    void login(QString username, QString password);

private:
    Ui::MainWindow *ui;
    log_in* loginwindow;
    sign_in* signupwindow;

};
#endif // MAINWINDOW_H
