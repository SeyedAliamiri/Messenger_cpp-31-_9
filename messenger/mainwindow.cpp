#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"chat.h"
#include<QMessageBox>
#include"main_user.h"
#include<QFile>
#include"main_page.h"
#include<QThread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    signupwindow=new sign_in(this);
    loginwindow=new log_in(this);
    QObject::connect(signupwindow,SIGNAL(signal_signup(QString, QString, QString, QString)),this,SLOT(signup(QString username, QString password, QString firstname, QString lastname)));
    QObject::connect(signupwindow,SIGNAL(already_have_account()),this,SLOT(already_have()));
    QObject::connect(loginwindow,SIGNAL(signal_login(QString,QString)),this,SLOT(login(QString username, QString password)));
    QObject::connect(loginwindow,SIGNAL(back()),this,SLOT(log_in_back()));

    first_check();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signup(QString username, QString password, QString firstname, QString lastname)
{
    QString first_name = "" , last_name = "";
    if(firstname != ""){
        first_name = "&firstname=" + firstname;
    }
    if(lastname != ""){
        last_name = "&lastname=" + lastname;
    }

    QUrl url("http://api.barafardayebehtar.ml:8080/signup?username=" + username + "&password=" + password + first_name + last_name);

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));

    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString code = jsonObj.value("code").toString();
            QString message = jsonObj.value("message").toString();

            if(code == "200"){
                signupwindow->close();
                login(username,password);

            }
            else{
                QMessageBox::critical(signupwindow, "Failure", message, QMessageBox::Ok);
            }
        }
    });
}

void MainWindow::login(QString username, QString password)
{
    QUrl url("http://api.barafardayebehtar.ml:8080/login?username=" + username + "&password=" + password);

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));

    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString code = jsonObj.value("code").toString();
            QString message = jsonObj.value("message").toString();
            QString token;

            if(code == "200"){
                loginwindow->close();
                QMessageBox::information(loginwindow, "Success", message, QMessageBox::Ok);
                token = jsonObj.value("token").toString();
                m=new main_user(token,username,password);
                //now what to do with token???
            }
            else{
                QMessageBox::critical(loginwindow, "Failure", message, QMessageBox::Ok);
            }
        }
    });
}

void MainWindow::first_check(){
    QFile f("main_user.json");
    if(f.exists()){
        f.open(QIODevice::ReadOnly);
        QString username;
        QString password;
        QString token;
        QJsonDocument doc;
        doc=QJsonDocument::fromJson( f.readAll());
        f.close();
        QJsonObject obj;
        obj=doc.object();
        username=obj.value("username").toString();
        password=obj.value("password").toString();
        token=obj.value("token").toString();
        m=new main_user(token,username,password);

    }
    else{
        signupwindow->show();

    }

}


void MainWindow::already_have(){
    signupwindow->close();
    loginwindow->show();

}

void MainWindow::log_in_back(){
    loginwindow->close();
    signupwindow->show();

};
//thread new class
class new_thread:public QThread{
public:
    new_thread(MainWindow* m){
        this->m=m;
    }
   void run(){
       for(;;){
           //if connection is ok
           //check connection is for you :))
           if(1){
               m->m->receive_message();
               m->m->check_for_new_chat();

           }

       }

   }


    MainWindow* m;


};






void MainWindow::start_main_page(){
    main_page * m_p=new main_page(m,this);
    QObject::connect(m,SIGNAL(find_new_message(chat* C)),m_p,SLOT(new_message(chat*)));
    QObject::connect(m,SIGNAL(find_new_member(chat*)),m_p,SLOT( new_member(chat*)));
    new_thread t1(this);
    t1.start();
    m_p->show();

}

