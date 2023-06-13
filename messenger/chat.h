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
   virtual int type_id();

private:
    QString name;
    //default=username
    QString username;
    QDateTime saved_date;
    QVector<Message> messages;
    bool able_to_send;
    bool is_favorite;
    int read_file();
    int save_file();
    virtual int send_message();
    virtual int receive_message();
    virtual void show_messages();


};

#endif // CHAT_H
