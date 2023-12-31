#ifndef MAIN_USER_H
#define MAIN_USER_H
#include<QString>
#include"chat.h"
#include"user.h"
#include"channel.h"
#include"group.h"
class main_page;
class MainWindow;
class new_thread;
class main_user :public QObject
{
    Q_OBJECT
    friend class main_page;
    friend class MainWindow;
    friend class new_thread;


public:
    main_user(QString tokenn,QString user_name,QString pass_word);
    ~main_user();

signals:
     void  find_new_message(chat*);
     void  find_new_member(chat*);
     void  messagebox(QString, QString, bool);
     void  loged_out();
     void  signal_connected(bool);
public slots:
     void  get_new_message(chat*);

private:
    void log_out();
    QString token;
    QString username;
    QString password;
    QString saved_date;
    QVector<chat*> users_arr;
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
    int flag_log_in;
    void creatgroup(QString group_name,QString group_title="");
    void creatchannel(QString channel_name,QString channel_title="");
    void joingroup(QString group_name);
    void joinchannel(QString channel_name);

};

#endif // MAIN_USER_H
