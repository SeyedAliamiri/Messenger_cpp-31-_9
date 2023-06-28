#ifndef CHAT_H
#define CHAT_H
#include<QString>
#include<QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
struct Message{
QString text;
QString message_date;
QString sender_userid;
};


class chat
{
    friend class main_user;
public:
    chat(QString,int);
   virtual int type_id()=0; //1->user 2->group 3->channel

protected:
    QString name;
    //default=username
    const QString username;
    QString saved_date;
    QVector<Message> messages;//is this really needed???
    bool able_to_send;
    bool is_favorite;
    int read_file();
    int save_file(Message);
    virtual int send_message(QString message, QString token)=0;//zz
    virtual int receive_message(QString token)=0;
    virtual void show_messages()=0;
    int send_resultcode;
    QString changedateformat(QString date);


};

#endif // CHAT_H
