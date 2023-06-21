#include "channel.h"


channel::channel(QString user_name): chat(user_name)
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
