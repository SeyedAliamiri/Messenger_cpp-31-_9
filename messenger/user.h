#ifndef USER_H
#define USER_H
#include "chat.h"

class user: public chat
{
public:
    user(QString);
    int type_id() override;
    int send_message() override;
    int receive_message() override;
    void show_messages() override;
};

#endif // USER_H
