#include "main_user.h"
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include"user.h"
#include"channel.h"
#include"group.h"
main_user::main_user(QString tokenn,QString user_name,QString pass_word)
{
    token = tokenn;
    username = user_name;
    password = pass_word;
    saved_date="";

}




int main_user::readfile(){
    //a
    //all users having chat
    //if file not found creat file
    QFile file("main_user.josn");
    if(file.exists()){
        if(file.open(QIODevice::ReadOnly)){
        QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
        QJsonObject obj=doc.object();
        int num=obj.value("number").toInt();
        saved_date=obj.value("saved_date").toString();
        for(int i=0;i<num;++i){
            QString userid= obj.value("user_id "+QString::number(i+1)).toString();
            int type_id=obj.value("type_id "+QString::number(i+1)).toInt();
            int flag_able_tosend=obj.value("able_to_send "+QString::number(i+1)).toInt();
            if(type_id==1){
               chat* temp=new user(userid,flag_able_tosend);
                users_arr.push_back(temp);

            }
            else if(type_id==2){
                chat* temp=new channel(userid,flag_able_tosend);
                 users_arr.push_back(temp);

            }
            else if(type_id==3){
                chat* temp=new group(userid,flag_able_tosend);
                 users_arr.push_back(temp);

            }

        }



        }
        else
        {
            //error in open file

        }

    }

}






int main_user::savefile(){
    //get users list
    QUrl u_url("http://api.barafardayebehtar.ml:8080/getuserlist?token=" + token );
    QNetworkAccessManager u_manager;
    QNetworkReply *u_reply = u_manager.get(QNetworkRequest(u_url)); // Send GET request
    int u_returncode = 0;
    while(u_reply->isRunning()){}
    if (u_reply->error() == QNetworkReply::NoError) {

        QByteArray data = u_reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QString code= jsonObj.value("code").toString();
        if(code.toInt()==200){
            std::string number_str=jsonObj.value("message").toString().toStdString().substr(15);
            int num=0;
            for(int i=0;;++i){
                if('0'<=number_str[i]&&number_str[i]<='9'){
                    num=num*10+number_str[i]-48;

                }
                else break;

            }
            for(int i= 0;i<num;++i){
                QString usernametemp=jsonObj.value("block "+QString::number(i)).toObject().value("user_name").toString();
                int flag =1;
                for(auto & it:users_arr){
                    if(it->username==usernametemp){
                        flag =0;break;
                        //means saved already
                    }
                    if(flag){
                        chat* temp=new user(usernametemp,1);
                        users_arr.push_back(temp);

                    }
                }
            }
        }
        u_returncode =  code.toInt();
    }

    // get group list
    QUrl g_url("http://api.barafardayebehtar.ml:8080/getgrouplist?token=" + token );
    QNetworkAccessManager g_manager;
    QNetworkReply *g_reply = g_manager.get(QNetworkRequest(g_url)); // Send GET request
    int g_returncode = 0;
    while(g_reply->isRunning()){}
    if (g_reply->error() == QNetworkReply::NoError) {

        QByteArray data = g_reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QString code= jsonObj.value("code").toString();
        if(code.toInt()==200){
            std::string number_str=jsonObj.value("message").toString().toStdString().substr(12);
            int num=0;
            for(int i=0;;++i){
                if('0'<=number_str[i]&&number_str[i]<='9'){
                    num=num*10+number_str[i]-48;

                }
                else break;

            }
            for(int i= 0;i<num;++i){
                QString groupnametemp=jsonObj.value("block "+QString::number(i)).toObject().value("user_name").toString();
                int flag =1;
                for(auto & it:users_arr){
                    if(it->username==groupnametemp){
                        flag =0;break;
                        //means saved already
                    }
                    if(flag){
                        chat* temp=new user(groupnametemp,1);
                        users_arr.push_back(temp);

                    }


                }

            }

        }


        g_returncode =  code.toInt();

    }

    //get channel list
    QUrl c_url("http://api.barafardayebehtar.ml:8080/getgrouplist?token=" + token );
    QNetworkAccessManager c_manager;
    QNetworkReply *c_reply = g_manager.get(QNetworkRequest(c_url)); // Send GET request
    int c_returncode = 0;
    while(c_reply->isRunning()){}
    if (c_reply->error() == QNetworkReply::NoError) {

        QByteArray data = c_reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QString code= jsonObj.value("code").toString();
        if(code.toInt()==200){
            std::string number_str=jsonObj.value("message").toString().toStdString().substr(12);
            int num=0;
            for(int i=0;;++i){
                if('0'<=number_str[i]&&number_str[i]<='9'){
                    num=num*10+number_str[i]-48;

                }
                else break;

            }
            for(int i= 0;i<num;++i){
                QString channelnametemp=jsonObj.value("block "+QString::number(i)).toObject().value("user_name").toString();
                int flag =1;
                for(auto & it:users_arr){
                    if(it->username==channelnametemp){
                        flag =0;break;
                        //means saved already
                    }
                    if(flag){
                        chat* temp=new user(channelnametemp,1);
                        //1??
                        users_arr.push_back(temp);

                    }


                }

            }

        }


        c_returncode =  code.toInt();

    }


}






int main_user::send_message(QString){
    //zz
    //send message-> [show]
}




int main_user::receive_message(){
    //
}




int main_user::show_Person_list(){

}





int main_user::show_Channel_list(){

}





int main_user::show_Group_list(){

}





int main_user::show_all(){

}





int main_user::sort(){
    //by time
    //zz
}
