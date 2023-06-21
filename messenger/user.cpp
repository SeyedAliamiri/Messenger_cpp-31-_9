#include "user.h"

user::user(QString user_name): chat(user_name)
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
