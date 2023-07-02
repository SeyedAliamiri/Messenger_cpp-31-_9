#include "create_channel_group.h"
#include "ui_create_channel_group.h"

create_channel_group::create_channel_group(bool channel1_group0, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_channel_group)
{
    ui->setupUi(this);

    if(channel1_group0){
        ui->label->setText("Creating Channel ...");
        ui->label_2->setText("Channel Name :");
        ui->label_3->setText("Channel Title :");
        this->setWindowTitle("Create New Channel");
    }
    else{
        ui->label->setText("Creating Group ...");
        ui->label_2->setText("Group Name :");
        ui->label_3->setText("Group Title :");
        this->setWindowTitle("Create New Group");
    }
}

create_channel_group::~create_channel_group()
{
    delete ui;
}

void create_channel_group::on_buttonBox_accepted()
{
    if(ui->name->text() != ""){
        emit signal_creat(ui->name->text(), ui->title->text());
    }
}

