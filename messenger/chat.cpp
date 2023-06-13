#include "chat.h"
#include "QFile"

chat::chat()
{

}
int chat::read_file(){

    QFile file(username+".txt");
    if(file.open(QIODevice::ReadOnly)){



        return 1;
    }
    else{

        return 0;
    }
}

int chat::save_file(){
    QFile file(username+".txt");
    if(file.open(QIODevice::Append)){
        QTextStream in(&file);



        return 1;
    }
    else{

        return 0;
    }
}
