#include "channel.h"
#include"chat.h"



channel::channel(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{

}

int channel::type_id(){
    return 3;
}
int channel::send_message(QString message, QString token){
    if(able_to_send){

        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkRequest request;
        request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/sendmessagegroup?token=" + token + "&dst=" + username + "&body=" + message));
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
                    emit new_message(this);
                    save_file(msg);

                }





            });

    return 1;
}
 const QVector<Message>& channel::show_messages(){

     return messages;

}


