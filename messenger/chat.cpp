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
    flag_read=1;
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
