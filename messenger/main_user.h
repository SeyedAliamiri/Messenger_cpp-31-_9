#ifndef MAIN_USER_H
#define MAIN_USER_H
#include<QString>

class main_user
{
public:
    main_user();

private:
    QString token;
    QString username;
    QString password;
    //USER* users_arr
    //USER* favorites
    int readfile();
    int savefile();
    int send_message(QString);
    int receive_message();
    int show_Person_list();
    int show_Channel_list();
    int show_Group_list();
    int show_all();
    int sort();

};

#endif // MAIN_USER_H
