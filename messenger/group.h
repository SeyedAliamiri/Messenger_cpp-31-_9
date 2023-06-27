#ifndef GROUP_H
#define GROUP_H
#include "chat.h"


class group: public chat
{
public:
    group(QString,int);
    int type_id() override;
    int send_message(QString message, QString token) override;
    int receive_message() override;
    void show_messages() override;


};

#endif // GROUP_H
