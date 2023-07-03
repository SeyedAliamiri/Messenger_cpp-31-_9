#ifndef USER_H
#define USER_H
#include "chat.h"

class user: public chat
{
     friend class main_page;

public:
    user(QString,int);
    ~user();
    int type_id() override;
    int send_message(QString message, QString token) override;
    int receive_message(QString token) override;
   const QVector<Message>& show_messages() override;
protected:
     int save_file(Message)override;
     int read_file()override;

};

#endif // USER_H
