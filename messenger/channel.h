#ifndef CHANNEL_H
#define CHANNEL_H

#include"chat.h"

class channel: public chat
{
public:
    channel(QString ,int);
    int type_id() override;
    int send_message(QString message, QString token) override;
    int receive_message() override;
    void show_messages() override;
};

#endif // CHANNEL_H
