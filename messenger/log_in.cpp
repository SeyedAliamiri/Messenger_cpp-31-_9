#include "log_in.h"
#include "ui_log_in.h"

log_in::log_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    this->setWindowIcon(QIcon(":/new/prefix1/picc/lock.png"));
}

log_in::~log_in()
{
    delete ui;
}

void log_in::on_pushButton_clicked()
{
    if(ui->password_lineedit->text().size()!=0&&ui->username_lineedit->text().size()!=0){
        //z
        emit signal_login(ui->username_lineedit->text(),ui->password_lineedit->text());
    }


}


void log_in::on_pushButton_2_clicked()
{
   emit back();


}

