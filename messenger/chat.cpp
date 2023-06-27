#include "chat.h"
#include<QJsonObject>
#include<QJsonDocument>
#include<QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
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
        message_struct.message_date=temp.value("date").toString();
        messages.push_back(message_struct);


    }



        return 1;
    }
    else{

        return 0;
    }
}

//thread
int chat::save_file(Message new_message){
    QFile file(username+".JSON");

    //if(newmessage){
    //append the new message
    //appent to vector
    //}

    if(file.open(QIODevice::ReadOnly)){
        QByteArray data;
        data=file.readAll();
        QJsonDocument json_data=QJsonDocument::fromJson(data);
        QJsonObject json_obj=json_data.object();
        json_obj.value("number")=json_obj.value("number").toInt()+1;
        QJsonObject new_data;
        new_data.value("text")=new_message.text;
        new_data.value("message_date")=new_message.message_date;
        new_data.value("sender_userid")=new_message.sender_userid;
        json_obj.value("message "+ QString::number( json_obj.value("number").toInt()))=new_data;
        file.close();
        file.open(QIODevice::WriteOnly);
        file.remove();
        file.close();
        file.open(QIODevice::WriteOnly);
        QJsonDocument new_doc={};
        new_doc.setObject(json_obj);
        file.write(new_doc.toJson());
        file.close();


        //aaa
        //


        return 1;
    }
    else{
    //means file doesnt exist
        file.open(QIODevice::WriteOnly);
        QJsonObject json_obj;
        json_obj.value("number")=1;
        QJsonObject new_data;
        new_data.value("text")=new_message.text;
        new_data.value("message_date")=new_message.message_date;
        new_data.value("sender_userid")=new_message.sender_userid;
        json_obj.value("message 1")=new_data;
        QJsonDocument doc;
        doc.setObject(json_obj);
        file.write(doc.toJson());
        file.close();


        return 0;
    }
}
