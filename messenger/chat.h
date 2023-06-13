#ifndef CHAT_H
#define CHAT_H
#include<QString>
#include<QDateTime>
struct Message{
QString text;
QDateTime date;
QString user_id;
};


class chat
{
public:
    chat();
   virtual int type_id()=0; //1->user 2->group 3->channel

protected:
    QString name;
    //default=username
    QString username;
    QDateTime saved_date;
    QVector<Message> messages;
    bool able_to_send;
    bool is_favorite;
    int read_file();
    int save_file();
    virtual int send_message()=0;
    virtual int receive_message()=0;
    virtual void show_messages()=0;


};

#endif // CHAT_H
