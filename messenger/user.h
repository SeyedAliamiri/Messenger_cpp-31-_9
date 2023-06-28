#ifndef USER_H
#define USER_H
#include "chat.h"

class user: public chat
{
public:
    user(QString,int);
    int type_id() override;
    int send_message(QString message, QString token) override;
    int receive_message(QString token) override;
    void show_messages() override;
};

#endif // USER_H
