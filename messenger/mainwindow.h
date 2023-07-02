#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "log_in.h"
#include "sign_in.h"
#include"main_user.h"
class new_thread;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class new_thread;
public:
    MainWindow(QWidget *parent = nullptr);
    void first_check();
    ~MainWindow();

public slots:
    void signup(QString username, QString password, QString firstname, QString lastname);
    void login(QString username, QString password);
    void already_have();
    void log_in_back();
    void update_();
private:

    void start_main_page();
    Ui::MainWindow *ui;
    log_in* loginwindow;
    sign_in* signupwindow;
    main_user* m;
};
#endif // MAINWINDOW_H
