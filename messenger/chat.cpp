#include "chat.h"
#include<QJsonObject>
#include<QJsonDocument>
#include<QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
chat::chat(QString user_name,int flag_able_tosend) : username(user_name)
{
    able_to_send = flag_able_tosend;
    name = username;
    saved_date="";
    read_file();
    flag_read=1;
}
int chat::read_file(){

    QFile file(username+".json");
    if(file.exists()){
    if(file.open(QIODevice::ReadOnly)){
    QByteArray data;
    data=file.readAll();
    file.close();
    QJsonDocument json_doc=QJsonDocument::fromJson(data);
    QJsonObject json_obj=json_doc.object();
    int message_count=json_obj.value("number").toInt();
    for(int i=1;i<=message_count;++i){
        QJsonObject temp=json_obj.value("message "+QString::number(i)).toObject();
        Message message_struct;
        message_struct.text=temp.value("text").toString();
        message_struct.sender_userid=temp.value("sender_userid").toString();
        message_struct.message_date=temp.value("date").toString();
        messages.push_back(message_struct);


    }

        return 1;
    }
    }
    else{
        //means file doesnt exist
        return 0;
    }

}

//thread
int chat::save_file(Message new_message){
    QFile file(username+".JSON");

    messages.push_back(new_message);
    saved_date=new_message.message_date;
    if(file.exists()){
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data;
        data=file.readAll();
        QJsonDocument json_data=QJsonDocument::fromJson(data);
        QJsonObject json_obj=json_data.object();
        json_obj.value("number")=json_obj.value("number").toInt()+1;
        QJsonObject new_data;
        new_data.insert("text",new_message.text);
        new_data.insert("message_date",new_message.message_date);
        new_data.insert("sender_userid",new_message.sender_userid);
        json_obj.insert("message "+ QString::number( json_obj.value("number").toInt()),new_data);
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
    //else

    //error in open file


    }
    else{
    //means file doesnt exist
        if(file.open(QIODevice::WriteOnly)){
        QJsonObject json_obj;
        json_obj.insert("number",1);
        QJsonObject new_data;
        new_data.insert("text",new_message.text);
        new_data.insert("message_date",new_message.message_date);
        new_data.insert("sender_userid",new_message.sender_userid);
        json_obj.insert("message 1",new_data);
        QJsonDocument doc;
        doc.setObject(json_obj);
        file.write(doc.toJson());
        file.close();


        return 1;
    }
        //else

        //error in open file

    }
    return 1;
}

QString chat::changedateformat(QString date){
    QString newdate = "";
    for(auto i:date){
        if(i >= '0' && i<= '9')
            newdate += i;
    }
    return newdate;
}
