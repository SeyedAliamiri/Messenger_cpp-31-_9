#include "channel.h"




channel::channel(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{

}

int channel::type_id(){
    return 3;
}
int channel::send_message(QString message, QString token){
    if(able_to_send){
        QUrl url("http://api.barafardayebehtar.ml:8080/sendmessagegroup?token=" + token + "&dst=" + username + "&body=" + message);
        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(url)); // Send GET request

        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() == QNetworkReply::NoError) {

                QByteArray data = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();
                QString code= jsonObj.value("code").toString();

                send_resultcode = code.toInt();

            }
        }  );
        return 1;
    }
    return 0;
}
int channel::receive_message(QString token){
    while(true){
        QString date = "";
        if(saved_date != ""){
            date = "&date=" + changedateformat(saved_date);
        }
        QUrl url("http://api.barafardayebehtar.ml:8080//getchannelchats?token=" + token + "&dst=" + username + date);

        QNetworkAccessManager manager;
        QNetworkReply *reply = manager.get(QNetworkRequest(url)); // Send GET request
        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray data = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();


               if( jsonObj.constFind("block 0") != jsonObj.end()){
                   QJsonObject block0 = jsonObj.value("block 0").toObject();
                   Message msg;
                   msg.message_date = block0.value("date").toString();
                   msg.sender_userid = block0.value("src").toString();
                   msg.text = block0.value("body").toString();
                   flag_read=0;
                   save_file(msg);
               }

            }
        });
    }
    return 1;
}
 const QVector<Message>& channel::show_messages(){

     return messages;

}


