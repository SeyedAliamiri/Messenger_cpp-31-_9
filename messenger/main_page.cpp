#include "main_page.h"
#include "ui_main_page.h"
#include"chat.h"
#include"user.h"
#include"channel.h"
#include<QFont>
main_page::main_page(main_user* mainuser,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_page)
{
    ui->setupUi(this);
    m=mainuser;
}

main_page::~main_page()
{
    delete ui;
}

void main_page::on_all_button_clicked()
{
    QVector<chat*> members;
    members=m->show_all();




}
void main_page::set_member_list(QVector<chat*> members){
    ui->member_list->clear();
    for(auto & it:members){
        ui->member_list->addItem("");
        int count=ui->member_list->count();

        QListWidgetItem* item=ui->member_list->item(count-1);
        item->setText(it->username);
        QFont f;
        f.setFamily("Berlin Sans FB Demi");
        f.setPointSize(16);
        item->setFont(f);
        QBrush b;
        if(it->flag_read){
           QColor c;
           c.setBlue(225);
           c.setRed(73);
           c.setAlpha(255);
           c.setGreen(225);
            b.setColor(c);
        }
        else{
            QColor c;
            c.setBlue(182);
            c.setRed(57);
            c.setAlpha(255);
            c.setGreen(117);
             b.setColor(c);
        }
        item->setBackground(b);
        if(it->flag_read){

            item->setCheckState(Qt::Checked);
        }
        else
            item->setCheckState(Qt::Unchecked);


    }


}

void main_page::on_member_list_itemClicked(QListWidgetItem *item)
{
    QString username=item->text();
    QVector<Message> messages;
    for(auto & it:m->users_arr){
        if(it->username==username){
            messages=it->show_messages();
            it->flag_read=1;
            clicked_chat=it;
            break;
        }

    }

}

void main_page::set_messages_graphicview(QVector<Message> messages){
    if(clicked_chat->able_to_send){
        ui->send_button->setEnabled(1);
        ui->new_message_text_edit->setEnabled(1);

    }
    //z
    //delete all messages and show new messages(refresh)


}
