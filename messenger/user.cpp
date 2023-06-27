#include "user.h"

user::user(QString user_name,int flag_able_tosend): chat(user_name,flag_able_tosend)
{

}
int user::type_id(){
    return 1;
}


int user::send_message() {
    return 1;
}

int user::receive_message(){
    return 1;
}
void user::show_messages(){

}
