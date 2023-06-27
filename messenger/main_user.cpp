#include "main_user.h"
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include"user.h"
#include"channel.h"
#include"group.h"
main_user::main_user(QString tokenn,QString user_name,QString pass_word)
{
    token = tokenn;
    username = user_name;
    password = pass_word;
    saved_date="";

}

int main_user::readfile(){
    //a
    //all users having chat
    //if file not found creat file
    QFile file("main_user.josn");
    if(file.exists()){
        if(file.open(QIODevice::ReadOnly)){
        QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
        QJsonObject obj=doc.object();
        int num=obj.value("number").toInt();
        saved_date=obj.value("saved_date").toString();
        for(int i=0;i<num;++i){
            QString userid= obj.value("user_id "+QString::number(i+1)).toString();
            int type_id=obj.value("type_id "+QString::number(i+1)).toInt();
            int flag_able_tosend=obj.value("able_to_send "+QString::number(i+1)).toInt();
            if(type_id==1){
               chat* temp=new user(userid,flag_able_tosend);
                users_arr.push_back(temp);

            }
            else if(type_id==2){
                chat* temp=new channel(userid,flag_able_tosend);
                 users_arr.push_back(temp);

            }
            else if(type_id==3){
                chat* temp=new group(userid,flag_able_tosend);
                 users_arr.push_back(temp);

            }

        }



        }
        else
        {
            //error in open file

        }

    }



}
int main_user::savefile(){
    //a
    //check list if new chat
    //append to file
    //append vector
    //vector sort
}
int main_user::send_message(QString){
    //zz
    //send message-> [show]
}
int main_user::receive_message(){
    //
}
int main_user::show_Person_list(){

}
int main_user::show_Channel_list(){

}
int main_user::show_Group_list(){

}
int main_user::show_all(){

}
int main_user::sort(){
    //by time
    //zz
}
