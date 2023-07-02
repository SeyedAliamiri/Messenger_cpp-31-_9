#include "main_page.h"
#include "create_channel_group.h"
#include "join_channel_group.h"
#include "QMessageBox"
#include "ui_main_page.h"
#include"chat.h"
#include"user.h"
#include"channel.h"
#include<QFont>

#define userpic ":/new/prefix1/user.png"
#define grouppic ":/new/prefix1/group.png"
#define channelpic ":/new/prefix1/channel.png"

main_page::main_page(main_user* mainuser,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::main_page)
{
    ui->setupUi(this);
    m = mainuser;
    clicked_chat=nullptr;

    ui->scrollArea->setWidget(ui->widget_2);
    member_list_type_id=0;

    QObject::connect(m, SIGNAL(messagebox(QString, QString, bool)), this,SLOT(show_messagebox(QString, QString, bool)));
    on_all_button_clicked();
    ui->create_group->setIcon(QIcon(":/new/prefix1/add_g.png"));
    ui->create_channel->setIcon(QIcon(":/new/prefix1/add.jpg"));
    ui->new_user->setIcon(QIcon(":/new/prefix1/add_u.png"));
    ui->newusergroupBox->hide();


}

main_page::~main_page()
{
    delete ui;
}

void main_page::on_all_button_clicked()
{
    QVector<chat*> members;
    members=m->show_all();
    set_member_list(members);
    member_list_type_id=4;


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

        if(it->type_id()==1){
            item->setIcon(QIcon(userpic));
        }
        else if(it->type_id()==2){
            item->setIcon(QIcon(grouppic));
        }
        else if(it->type_id()==3){
            item->setIcon(QIcon(channelpic));
        }

        if(it->flag_read){

            item->setCheckState(Qt::Checked);
        }
        else
            item->setCheckState(Qt::Unchecked);


    }


}

void main_page::on_member_list_itemClicked(QListWidgetItem *item)
{

    QVector<Message> messages;
    int num=0;
    for(auto& it:m->users_arr){

        if( it->type_id()==this->member_list_type_id || member_list_type_id == 4){
            if(num==ui->member_list->currentRow()){
                clicked_chat=it;
                messages=it->show_messages();
                break;
            }
            ++num;
        }


    }

    set_messages_graphicview(messages);

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

    ui->chatname->setText(clicked_chat->username);
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
        if( it->sender_userid == m->username ){    //?
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

void main_page::new_message(chat* C)
{
if(C->type_id()==member_list_type_id||member_list_type_id==4){
    if(member_list_type_id==4){
        on_all_button_clicked();
    }
        else if(member_list_type_id==3){
        on_group_button_clicked();

    }
    else if(member_list_type_id==2){
        on_channel_button_clicked();

    }
    else
        on_users_button_clicked();

    if(clicked_chat->username==C->username&&clicked_chat->type_id()==C->type_id()){
        set_messages_graphicview(C->messages);

    }


}




}

void main_page::on_group_button_clicked()
{
    QVector<chat*> members;
    members=m->show_Group_list();
    set_member_list(members);
    member_list_type_id=2;

}


void main_page::on_channel_button_clicked()
{
    QVector<chat*> members;
    members=m->show_Channel_list();
    set_member_list(members);
    member_list_type_id=3;
}


void main_page::on_send_button_clicked()
{
    if(ui->new_message_text_edit->toPlainText().size()!=0){

        QString message=ui->new_message_text_edit->toPlainText();
        clicked_chat->send_message(message,m->token);
        ui->new_message_text_edit->clear();

    }


}


void main_page::on_users_button_clicked()
{
    QVector<chat*> members;
    members=m->show_Person_list();
    set_member_list(members);
    member_list_type_id=1;
}

void main_page::new_member(chat* C){
    if(member_list_type_id==4||member_list_type_id==C->type_id()){
        if(member_list_type_id==4){
            on_all_button_clicked();
        }
            else if(member_list_type_id==3){
            on_group_button_clicked();

        }
        else if(member_list_type_id==2){
            on_channel_button_clicked();

        }
        else
            on_users_button_clicked();

    }

}




void main_page::on_create_channel_clicked()
{
    create_channel_group* creatchannel = new create_channel_group(1,this);
    creatchannel->show();
    QObject::connect(creatchannel, SIGNAL(signal_creat(QString, QString)), this, SLOT(createchannel(QString, QString)));
}


void main_page::on_join_channel_clicked()
{
    join_channel_group* joinchannel = new join_channel_group(1 , this);
    joinchannel->show();
    QObject::connect(joinchannel, SIGNAL(signal_join(QString)), this, SLOT(joinchannel(QString)));
}

void main_page::joinchannel(QString channelname)
{
    m->joinchannel(channelname);
}

void main_page::joingroup(QString groupname)
{
    m->joingroup(groupname);
}

void main_page::createchannel(QString channelname, QString channeltitle)
{
    m->creatchannel(channelname,channeltitle);
}

void main_page::creategroup(QString groupname, QString grouptitle)
{
    m->creatgroup(groupname, grouptitle);
}

void main_page::show_messagebox(QString title, QString text, bool success)
{
    if(success){
        QMessageBox::information(this, title,text);
    }
    else{
        QMessageBox::critical(this,title,text);
    }
}


void main_page::on_join_group_clicked()
{
    join_channel_group* joingroup = new join_channel_group(0 , this);
    joingroup->show();
    QObject::connect(joingroup, SIGNAL(signal_join(QString)), this, SLOT(joingroup(QString)));
}


void main_page::on_create_group_clicked()
{
    create_channel_group* creatgroup = new create_channel_group(0,this);
    creatgroup->show();
    QObject::connect(creatgroup, SIGNAL(signal_creat(QString, QString)), this, SLOT(creategroup(QString, QString)));
}


void main_page::on_new_user_clicked()
{
    ui->newusergroupBox->show();
}


void main_page::on_newusercancel_clicked()
{
    ui->newuserlineEdit->clear();

    ui->newusergroupBox->hide();
}


void main_page::on_newuserok_clicked()
{
    if(ui->newuserlineEdit->text() != ""){
        clicked_chat = new user(ui->newuserlineEdit->text(),1);
        QObject::connect(clicked_chat, SIGNAL(messagebox(QString, QString, bool)), this,SLOT(show_messagebox(QString, QString, bool)));


        ui->send_button->setEnabled(clicked_chat->able_to_send);
        ui->new_message_text_edit->setEnabled(clicked_chat->able_to_send);
        ui->chatname->setText(clicked_chat->username);
        for(auto& msg:mesageslayout) delete msg;
        for(auto& msg:mesagestext) msg->close();
        mesageslayout.clear();
        mesagestext.clear();

        ui->newuserlineEdit->clear();
        ui->newusergroupBox->hide();
    }
}

