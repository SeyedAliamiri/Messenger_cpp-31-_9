#include "user.h"

user::user(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{

}
int user::type_id(){
    return 1;
}

//returns the code in servers reply (if no reply returns 0) //return might have bug
int user::send_message(QString message, QString token) {
    if(able_to_send){
        QUrl url("http://api.barafardayebehtar.ml:8080/sendmessageuser?token=" + token + "&dst=" + username + "&body=" + message);
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

int user::receive_message(){
    return 1;
}
void user::show_messages(){

}
