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
        int returncode = 0;
        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() == QNetworkReply::NoError) {

                QByteArray data = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObj = jsonDoc.object();
                QString code= jsonObj.value("code").toString();

                returncode =  code.toInt();

            }
        }  );
        return returncode;
    }
    return 0;
}
int channel::receive_message(){
    return 1;
}
void channel::show_messages(){

}
