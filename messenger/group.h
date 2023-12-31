#ifndef GROUP_H
#define GROUP_H
#include "chat.h"

class group: public chat
{
    friend class main_page;

public:
    group(QString,int);
    ~group();
    int type_id() override;
    int send_message(QString message, QString token) override;
    int receive_message(QString token) override;
   const QVector<Message>& show_messages() override;
protected:
     int save_file(Message)override;
     int read_file()override;


};

#endif // GROUP_H
