#ifndef GROUP_H
#define GROUP_H
#include "chat.h"


class group: public chat
{
public:
    group();
    int type_id() override;
    int send_message() override;
    int receive_message() override;
    void show_messages() override;


};

#endif // GROUP_H
