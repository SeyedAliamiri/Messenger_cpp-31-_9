#include "channel.h"
#include"chat.h"
#include <QDir>
#include<QFile>


channel::channel(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{
channel::read_file();
}

int channel::type_id(){
    return 3;
}
int channel::send_message(QString message, QString token){
    if(able_to_send){

        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkRequest request;
        request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/sendmessagechannel?token=" + token + "&dst=" + username + "&body=" + message));
        manager->get(request);

        QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
            if (reply->error()) { qDebug() << reply->errorString(); return; }

                QByteArray data = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();
                QString code= jsonObj.value("code").toString();

                send_resultcode = code.toInt();

            });
        return 1;
    }
    return 0;
}

int channel::save_file(Message new_message){
    for(auto& it:messages){
        if(it.message_date==new_message.message_date&&it.sender_userid==new_message.sender_userid){
            return 0;

        }

    }


    QFile file(QDir::currentPath()+"/channels/" +username+".json");

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



int channel::read_file(){
        QFile file(QDir::currentPath()+"/channels/" +username+".json");
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



int channel::receive_message(QString token){

        QString date = "";
        if(saved_date != ""){
            date = "&date=" + changedateformat(saved_date);
        }


        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkRequest request;
        request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080//getchannelchats?token=" + token + "&dst=" + username + date));
        manager->get(request);

        QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
            if (reply->error()) { qDebug() << reply->errorString(); return; }

                QByteArray data = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();

                QString s=jsonObj.value("message").toString();
                std::string number_str=s.toStdString().substr(11);
                int num=0;
                for(int i=0;;++i){
                    if('0'<=number_str[i]&&number_str[i]<='9'){
                        num=num*10+number_str[i]-48;

                    }
                    else break;

                }

                for(int i=0;i<num;++i){
                    Message msg;
                    msg.message_date =jsonObj.value("block "+QString::number(i)).toObject().value("date").toString();
                    msg.sender_userid = jsonObj.value("block "+QString::number(i)).toObject().value("src").toString();
                    msg.text = jsonObj.value("block "+QString::number(i)).toObject().value("body").toString();
                    flag_read=0;
                    saved_date=jsonObj.value("block "+QString::number(i)).toObject().value("date").toString();

                    emit new_message(this);
                    save_file(msg);

                }





            });

    return 1;
}
 const QVector<Message>& channel::show_messages(){

     return messages;

}

 channel::~channel(){
     QFile file(QDir::currentPath()+"/channels/" +username+".json");
     if(file.exists()){

         file.remove();
     }




 }
