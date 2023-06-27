#include "channel.h"


channel::channel(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{

}

int channel::type_id(){
    return 3;
}
int channel::send_message(){
    return 1;
}
int channel::receive_message(){
    return 1;
}
void channel::show_messages(){

}
