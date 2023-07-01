#include "group.h"
#include"chat.h"

group::group(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{

}

int group::type_id(){
    return 2;
}

int group::send_message(QString message, QString token){
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
int group::receive_message(QString token) {
    while(true){
        QString date = "";
        if(saved_date != ""){
            date = "&date=" + changedateformat(saved_date);
        }


        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkRequest request;
        request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080//getgroupchats?token=" + token + "&dst=" + username + date));
        manager->get(request);

        QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
            if (reply->error()) { qDebug() << reply->errorString(); return; }
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
                   emit new_message(this);
                   save_file(msg);
               }

            });
    }
    return 1;
}
const QVector<Message>& group::show_messages(){
    return messages;
}
