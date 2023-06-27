#include "group.h"

group::group(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{

}

int group::type_id(){
    return 2;
}

int group::send_message(){
    return 1;
}
int group::receive_message() {
    return 1;
}
void group::show_messages(){

}
