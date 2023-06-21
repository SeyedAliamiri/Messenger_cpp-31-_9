#include "chat.h"
#include "QFile"

chat::chat(QString user_name) : username(user_name)
{
    name = username;

}
int chat::read_file(){

    QFile file(username+".txt");
    if(file.open(QIODevice::ReadOnly)){


        //aaa
        //reads the file and save them in messsages
        //


        return 1;
    }
    else{

        return 0;
    }
}

//thread
int chat::save_file(){
    QFile file(username+".Json");

    //if(newmessage){
    //append the new message
    //appent to vector
    //}


    if(file.open(QIODevice::Append)){
        QTextStream in(&file);

        //aaa
        //


        return 1;
    }
    else{

        return 0;
    }
}
