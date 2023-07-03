#include "sign_in.h"
#include "ui_sign_in.h"
#include"log_in.h"

sign_in::sign_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
    this->ui->diffrent_error->hide();
    this->setWindowTitle("Signup");
    this->setWindowIcon(QIcon(":/new/prefix1/picc/lock.png"));
}

sign_in::~sign_in()
{
    delete ui;
}

void sign_in::on_password_2_lineedit_textChanged(const QString &arg1)
{
 if(ui->username_lineedit->text().size()!=0&&ui->password_lineedit->text().size()!=0){
     if(ui->password_2_lineedit->text()==ui->password_lineedit->text()){
          ui->diffrent_error->hide();
         ui->sign_in_button->setEnabled(1);

     }
     else{

         ui->diffrent_error->show();

     }

 }

}


void sign_in::on_sign_in_button_clicked()
{
    //z
    emit signal_signup(ui->username_lineedit->text(), ui->password_lineedit->text(), ui->firstname->text(), ui->lastname->text());


}


void sign_in::on_alreadyhaveacount_clicked()
{
   emit already_have_account();


}

