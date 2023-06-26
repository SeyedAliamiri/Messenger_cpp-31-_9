#include "chat.h"
#include<QJsonObject>
#include<QJsonDocument>>
#include<QFile>
chat::chat(QString user_name) : username(user_name)
{
    name = username;

}
int chat::read_file(){

    QFile file(username+".json");
    if(file.open(QIODevice::ReadOnly)){
    QByteArray data;
    data=file.readAll();
    file.close();
    QJsonDocument json_doc=QJsonDocument::fromJson(data);
    QJsonObject json_obj=json_doc.object();
    int message_count=json_obj.value("number").toInt();
    for(int i=0;i<message_count;++i){
        QJsonObject temp=json_obj.value("message "+QString::number(i)).toObject();
        Message message_struct;
        message_struct.text=temp.value("body").toString();
        message_struct.sender_userid=temp.value("sender").toString();
        message_struct.massage_date=temp.value("date").toString();
        messages.push_back(message_struct);


    }



        return 1;
    }
    else{

        return 0;
    }
}

//thread
int chat::save_file(){
    QFile file(username+".Json");

    //if(newmessage){
    //append the new message
    //appent to vector
    //}


    if(file.open(QIODevice::Append)){
        QTextStream in(&file);

        //aaa
        //


        return 1;
    }
    else{

        return 0;
    }
}
