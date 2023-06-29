#ifndef MAIN_USER_H
#define MAIN_USER_H
#include<QString>
#include"chat.h"
#include"user.h"
#include"channel.h"
#include"group.h"
class main_page;
class main_user
{
    friend class main_page;
public:
    main_user(QString tokenn,QString user_name,QString pass_word);

private:
    QString token;
    QString username;
    QString password;
    QString saved_date;
    QVector<chat*> users_arr;
    QVector<chat*> favorites;
    int readfile();
    int savefile(QString username,int type_id,int flag);
    int send_message(QString, chat*);
    int check_for_new_chat();
    int receive_message();
    QVector<chat*> show_Person_list();
    QVector<chat*> show_Channel_list();
    QVector<chat*> show_Group_list();
    QVector<chat*> show_all();
    int sort();

    void creatgroup(QString group_name,QString group_title="");
    void creatchannel(QString channel_name,QString channel_title="");
    void joingroup(QString group_name);
    void joinchannel(QString channel_name);

};

#endif // MAIN_USER_H
