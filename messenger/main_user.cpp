#include "main_user.h"
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include"user.h"
#include"channel.h"
#include"group.h"
#include<algorithm>
#include <QMessageBox>
#include<QDir>
main_user::main_user(QString tokenn,QString user_name,QString pass_word)
{
    token = tokenn;
    username = user_name;
    password = pass_word;
    saved_date="";
    flag_log_in=1;
    readfile();


}

int main_user::readfile(){
    //a
    //all users having chat
    //if file not found creat file
    QFile file("main_user.json");
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
               QObject::connect(temp,SIGNAL(new_message(chat*)),this,SLOT(get_new_message(chat*)));
                users_arr.push_back(temp);

            }
            else if(type_id==3){
                chat* temp=new channel(userid,flag_able_tosend);
                QObject::connect(temp,SIGNAL(new_message(chat*)),this,SLOT(get_new_message(chat*)));
                 users_arr.push_back(temp);

            }
            else if(type_id==2){
                chat* temp=new group(userid,flag_able_tosend);
                QObject::connect(temp,SIGNAL(new_message(chat*)),this,SLOT(get_new_message(chat*)));
                 users_arr.push_back(temp);

            }

        }



        }
        else
        {
            //error in open file

        }

    }
return 0;
}


int main_user::check_for_new_chat(){

    //get users list

    QNetworkAccessManager* u_manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/getuserlist?token=" + token ));
    u_manager->get(request);

    //int u_returncode = 0;
    QObject::connect(u_manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply* u_reply) {
        if (u_reply->error()) { return; }

        QByteArray data = u_reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QString code= jsonObj.value("code").toString();
        if(code=="200"){
            std::string number_str=jsonObj.value("message").toString().toStdString().substr(20);
            int num=0;
            for(int i=0;;++i){
                if('0'<=number_str[i]&&number_str[i]<='9'){
                    num=num*10+number_str[i]-48;

                }
                else break;

            }
            for(int i= 0;i<num;++i){
                QString usernametemp=jsonObj.value("block "+QString::number(i)).toObject().value("src").toString();
                int flag =1;
                for(auto & it:users_arr){
                    if(it->username==usernametemp&&it->type_id()==1){
                        flag =0;break;
                        //means saved already
                    }}
                    if(flag){
                        chat* temp=new user(usernametemp,1);
                        QObject::connect(temp,SIGNAL(new_message(chat*)),this,SLOT(get_new_message(chat*)));
                        savefile(usernametemp,1,1);
                        users_arr.push_back(temp);





                        emit find_new_member(temp);


                    }
                }

        }
        //u_returncode =  code.toInt();
    }
);
    // get group list

    QNetworkAccessManager* g_manager = new QNetworkAccessManager(this);
    QNetworkRequest request2;
    request2.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/getgrouplist?token=" + token ));
    g_manager->get(request2);

    //int g_returncode = 0;
    QObject::connect(g_manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *g_reply) {
              if (g_reply->error()) {  return; }

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
                QString groupnametemp=jsonObj.value("block "+QString::number(i)).toObject().value("group_name").toString();
                int flag =1;
                for(auto & it:users_arr){
                    if(it->username==groupnametemp&&it->type_id()==2){
                        flag =0;break;
                        //means saved already
                    }}
                    if(flag){
                        chat* temp=new group(groupnametemp,1);
                         savefile(groupnametemp,2,1);
                         QObject::connect(temp,SIGNAL(new_message(chat*)),this,SLOT(get_new_message(chat*)));
                        users_arr.push_back(temp);


                        emit find_new_member(temp);


                    }


                }

            }




       // g_returncode =  code.toInt();

    });

    //get channel list
    QNetworkAccessManager* c_manager = new QNetworkAccessManager(this);
    QNetworkRequest request3;
    request3.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/getchannellist?token=" + token ));
    c_manager->get(request3);


    //int c_returncode = 0;
    QObject::connect(c_manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *c_reply) {
              if (c_reply->error()) {return; }

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
                QString channelnametemp=jsonObj.value("block "+QString::number(i)).toObject().value("channel_name").toString();
                int flag =1;
                for(auto & it:users_arr){
                    if(it->username==channelnametemp&&it->type_id()==3){
                        flag =0;break;
                        //means saved already
                    }}
                    if(flag){
                        chat* temp=new channel(channelnametemp,1);
                        //1??
                        savefile(channelnametemp,3,1);
                        //1??
                        QObject::connect(temp,SIGNAL(new_message(chat*)),this,SLOT(get_new_message(chat*)));
                        users_arr.push_back(temp);



                        emit find_new_member(temp);


                    }


                }



        }


        //c_returncode =  code.toInt();

    });

return 1;

}







int main_user::savefile(QString username,int type_id,int flag){
    int numb=0;
    QJsonDocument doc;
    QJsonObject obj;
    QFile file("main_user.json");
    if(file.exists()){
        file.open(QIODevice::ReadOnly);
         doc=QJsonDocument::fromJson(file.readAll());
         obj=doc.object();
         numb=obj.value("number").toInt();
         file.close();
         file.remove();
         obj["number"]=numb+1;
         obj.insert("user_id "+QString::number(numb+1),username);
         obj.insert("type_id "+QString::number(numb+1),type_id);
         obj.insert("able_to_send "+QString::number(numb+1),flag);
         QJsonDocument doc2;
         doc2.setObject(obj);
         file.open(QIODevice::WriteOnly);
         file.write(doc2.toJson());
         file.close();

    }
    else{
     obj.insert("token",token);
     obj.insert("password",password);
     obj.insert("username",this->username);
     obj.insert("number",numb+1);
     obj.insert("user_id "+QString::number(numb+1),username);
     obj.insert("type_id "+QString::number(numb+1),type_id);
     obj.insert("able_to_send "+QString::number(numb+1),flag);
     QJsonDocument doc2;
     doc2.setObject(obj);
     file.open(QIODevice::WriteOnly);
     file.write(doc2.toJson());
     file.close();

    }

return 1;
}






int main_user::send_message(QString message, chat* chat1){
    //zz
    chat1->send_message(message, token);

    return chat1->send_resultcode;
}




int main_user::receive_message(){

    for(auto & it:users_arr){

        it->receive_message(token);
    }
    return 1;
}




 QVector<chat*> main_user::show_Person_list(){
    sort();
    QVector<chat*> temp;
    for(auto & it:users_arr){
        if(it->type_id()==1){
            temp.push_back(it);

        }

    }



    return temp;
}





QVector<chat*> main_user::show_Channel_list(){
    sort();
    QVector<chat*> temp;
    for(auto & it:users_arr){
        if(it->type_id()==3){
            temp.push_back(it);

        }

    }



    return temp;
}





QVector<chat*> main_user::show_Group_list(){
    sort();
    QVector<chat*> temp;
    for(auto & it:users_arr){
        if(it->type_id()==2){
            temp.push_back(it);

        }

    }

    return temp;


}





QVector<chat*> main_user::show_all(){
  sort();
  return users_arr;
}





int main_user::sort(){
    //by time
    //zz
    std::sort(users_arr.begin() , users_arr.end() , [](const chat* a, const chat* b){ return a->saved_date>=b->saved_date;});
    return 1;
}

void main_user::creatgroup(QString group_name,QString group_title)
{
    QString grouptitle = "";
    if(group_title != ""){
        grouptitle = "&group_title=" + group_title;
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/creategroup?token=" + token + "&group_name=" + group_name + grouptitle));
    manager->get(request);

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
              if (reply->error()) {  return; }
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString code = jsonObj.value("code").toString();
            QString message = jsonObj.value("message").toString();

            if(code == "200"){
                //success
                emit messagebox("Success", message, 1);
            }
            else{
               //fail
                emit messagebox("Fail", message, 0);
            }
        }
    );
}

void main_user::creatchannel(QString channel_name, QString channel_title)
{
    QString channeltitle = "";
    if(channel_title != ""){
        channeltitle = "&channel_title=" + channel_title;
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/createchannel?token=" + token + "&channel_name=" + channel_name + channeltitle));
    manager->get(request);

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
              if (reply->error()) {  return; }
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString code = jsonObj.value("code").toString();
            QString message = jsonObj.value("message").toString();

            if(code == "200"){
                //success
                emit messagebox("Success", message, 1);
            }
            else{
               //fail
                emit messagebox("Fail", message, 0);
            }
        }
    );
}

void main_user::joingroup(QString group_name)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/joingroup?token=" + token + "&group_name=" + group_name));
    manager->get(request);

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
              if (reply->error()) {  return; }
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString code = jsonObj.value("code").toString();
            QString message = jsonObj.value("message").toString();

            if(code == "200"){
                //success
                emit messagebox("Success", message, 1);
            }
            else{
               //fail
                emit messagebox("Fail", message, 0);
            }
        }
    );
}

void main_user::joinchannel(QString channel_name)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/joinchannel?token=" + token + "&channel_name=" + channel_name));
    manager->get(request);

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
              if (reply->error()) {  return; }
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString code = jsonObj.value("code").toString();
            QString message = jsonObj.value("message").toString();

            if(code == "200"){
                //success
                emit messagebox("Success", message, 1);
            }
            else{
               //fail
                emit messagebox("Fail", message, 0);
            }
        }
    );
}

void main_user::get_new_message(chat* C){
    emit find_new_message(C);

}

void main_user::log_out(){

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/logout?username=" + username + "&password=" + password));
    manager->get(request);

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
              if (reply->error()) {  return; }
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString code = jsonObj.value("code").toString();
            QString message = jsonObj.value("message").toString();

            if(code == "200"){
                flag_log_in=0;



                //success
                emit messagebox("Success", message, 1);
                emit loged_out();
            }
            else{
               //fail
                emit messagebox("Fail", message, 0);
            }
        });


};

main_user::~main_user(){
    QFile file("main_user.json");
    if(file.exists()){

       file.remove();

    }

    for(auto &it:users_arr){

        delete it;


    }





}
