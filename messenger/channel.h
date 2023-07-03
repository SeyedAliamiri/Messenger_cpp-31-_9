#ifndef CHANNEL_H
#define CHANNEL_H

#include"chat.h"

class channel: public chat
{
     friend class main_page;
public:

    channel(QString ,int);
    int type_id() override;
    int send_message(QString message, QString token) override;
    int receive_message(QString token) override;
    const QVector<Message>& show_messages() override;
protected:
     int save_file(Message)override;
     int read_file()override;

};

#endif // CHANNEL_H
