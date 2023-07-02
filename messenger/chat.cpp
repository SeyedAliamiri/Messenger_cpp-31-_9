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
        saved_date=message_struct.message_date=temp.value("message_date").toString();
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
    for(auto& it:messages){
        if(it.message_date==new_message.message_date&&it.sender_userid==new_message.sender_userid){
            return 0;

        }

    }


    QFile file(username+".json");

    messages.push_back(new_message);
    saved_date=new_message.message_date;
    if(file.exists()){
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data;
        data=file.readAll();
        QJsonDocument json_data=QJsonDocument::fromJson(data);
        QJsonObject json_obj=json_data.object();
        json_obj["number"]=json_obj.value("number").toInt()+1;
        QJsonObject new_data;
        new_data.insert("text",new_message.text);
        new_data.insert("message_date",new_message.message_date);
        new_data.insert("sender_userid",new_message.sender_userid);
        json_obj.insert("message "+ QString::number( json_obj.value("number").toInt()),new_data);
        file.close();
        file.remove();
        file.open(QIODevice::WriteOnly);
        QJsonDocument new_doc;
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
        else
            newdate += " ";
    }

    QStringList list = newdate.split(' ');
    int day = list[2].toInt();
    int hour = list[3].toInt();
    int min = list[4].toInt();
    int sec = list[5].toInt();

    sec++;
    if(sec>=60){
        sec = 0;
        min++;
        if(min>=60){
            min = 0;
            hour++;
            if(hour>=24){
                hour = 0;
                day++;
            }
        }
    }

    if(sec<=9)
        list[5] = "0" + QString::number(sec);
    else
       list[5] = QString::number(sec);

    if(min<=9)
        list[4] = "0" + QString::number(min);
    else
       list[4] = QString::number(min);

    if(hour<=9)
        list[3] = "0" + QString::number(hour);
    else
       list[3] = QString::number(hour);

    if(day<=9)
        list[2] = "0" + QString::number(day);
    else
       list[2] = QString::number(day);

    newdate = "";
    for(auto& i:list){
        newdate += i;
    }

    return newdate;
}
