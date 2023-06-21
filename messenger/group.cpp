#include "group.h"

group::group(QString user_name): chat(user_name)
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
