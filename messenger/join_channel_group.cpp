#include "join_channel_group.h"
#include "ui_join_channel_group.h"

join_channel_group::join_channel_group(bool channel1_group0, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::join_channel_group)
{
    ui->setupUi(this);
    if(channel1_group0){
        ui->label->setText("Joining Channel ...");
        ui->label_2->setText("Enter channel name:");
    }
    else{
        ui->label->setText("Joining Group ...");
        ui->label_2->setText("Enter Group name:");

    }
}

join_channel_group::~join_channel_group()
{
    delete ui;
}

void join_channel_group::on_buttonBox_accepted()
{
    if(ui->lineEdit->text() != ""){
        emit signal_join(ui->lineEdit->text());
    }
}

