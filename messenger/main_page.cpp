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
    ui->scrollArea->setWidget(ui->widget_2);
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

QString main_page::messageto_html(Message message)
{
    QString result = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd\">"
    "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">"
    "p, li { white-space: pre-wrap; }"
    "</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">"
    "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            "<span style=\" font-size:11pt; color:#891ace;\">" + message.sender_userid + ":</span></p>";
    QList<QString> splitedstring = message.text.split('\n');
    for(auto& a:splitedstring){
        result += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">" + a + "</p>";
    }


    result += "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            "<span style=\" font-size:8pt; color:#891ace;\">" + message.message_date + "</span></p></body></html>";
    return result;
}

void main_page::set_messages_graphicview(QVector<Message> messages){

    ui->send_button->setEnabled(clicked_chat->able_to_send);
    ui->new_message_text_edit->setEnabled(clicked_chat->able_to_send);


    //z
    //delete all messages and show new messages(refresh)

    for(auto& msg:mesageslayout) delete msg;
    for(auto& msg:mesagestext) msg->close();
    mesageslayout.clear();
    mesagestext.clear();

    //reverse is better or not reverse???
    QVector<Message>::iterator it;
    for(it = messages.begin(); it != messages.end() ; it++){
        QHBoxLayout* newlayout = new QHBoxLayout();
        QSpacerItem* space = new QSpacerItem(200,20);
        QTextBrowser* text = new QTextBrowser(this);
        text->setHtml(messageto_html(*it));
        text->setMinimumSize(100,100);
        if( it->sender_userid == clicked_chat->username ){    //?
            newlayout->addSpacerItem(space);
            newlayout->addWidget(text);
        }
        else{
            newlayout->addWidget(text);
            newlayout->addSpacerItem(space);
        }

        mesageslayout.push_back(newlayout);
        //mesagesspacer.push_back(space);
        mesagestext.push_back(text);
        ui->verticalLayout_4->addLayout(newlayout);

    }


}

void main_page::new_message()
{

}
