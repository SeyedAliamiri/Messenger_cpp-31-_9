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

    //first_check();
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

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl((QString)"http://api.barafardayebehtar.ml:8080/signup?username=" + username + (QString)"&password=" + password + first_name + last_name));
    manager->get(request);


    QObject::connect(manager, &QNetworkAccessManager::finished,
          this, [=](QNetworkReply *reply) {
              if (reply->error()) {
                  qDebug() << reply->errorString();
                  return;
              }

              QByteArray data = reply->readAll();
              QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
              QJsonObject jsonObj = jsonDoc.object();
              QString code = jsonObj.value("code").toString();
              QString message = jsonObj.value("message").toString();

              if(code == "200"){
                  signupwindow->close();
                  delete signupwindow;
                  login(username,password);
              }
              else{
                  QMessageBox::critical(this, "signup Failure", message, QMessageBox::Ok);
              }
          }
      );


}

void MainWindow::login(QString username, QString password)
{

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/login?username=" + username + "&password=" + password));
    manager->get(request);

    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
              if (reply->error()) { qDebug() << reply->errorString(); return; }

              QByteArray data = reply->readAll();
              QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
              QJsonObject jsonObj = jsonDoc.object();
              QString code = jsonObj.value("code").toString();
              QString message = jsonObj.value("message").toString();
              QString token;

              if(code == "200"){
                  QMessageBox::information(this, "Success", message, QMessageBox::Ok);
                  token = jsonObj.value("token").toString();
                  QFile file("main_user.json");
                  QJsonObject obj;
                  obj.insert("username",username);
                  obj.insert("token",token);
                  qDebug()<<token;
                  qDebug()<<jsonDoc;
                  obj.insert("password",password);
                  file.open(QIODevice::WriteOnly);
                  QJsonDocument doc;
                  doc.setObject(obj);
                  file.write(doc.toJson());
                  file.close();
                  m = new main_user(token, username, password);
                  if(loginwindow==nullptr){
                      delete loginwindow;
                        loginwindow=nullptr;
                  }
                  start_main_page();


                  //now what to do with token??? //save token in file
              }
              else{
                  QMessageBox::critical(this, "login Failure", message, QMessageBox::Ok);
              }
          }
      );


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
        start_main_page();

    }
    else{
        signupwindow=new sign_in(this);
        QObject::connect(signupwindow,SIGNAL(signal_signup(QString, QString, QString, QString)),this,SLOT(signup(QString, QString, QString, QString)));
        QObject::connect(signupwindow,SIGNAL(already_have_account()),this,SLOT(already_have()));
        signupwindow->show();
    }

}


void MainWindow::already_have(){
    signupwindow->close();
    _sleep(100);
    delete signupwindow;
    signupwindow=nullptr;
    loginwindow=new log_in(this);
    QObject::connect(loginwindow,SIGNAL(signal_login(QString,QString)),this,SLOT(login(QString, QString)));
    QObject::connect(loginwindow,SIGNAL(back()),this,SLOT(log_in_back()));
    loginwindow->show();

}

void MainWindow::log_in_back(){
    loginwindow->close();
    delete loginwindow;
    loginwindow=nullptr;
    signupwindow=new sign_in(this);
    QObject::connect(signupwindow,SIGNAL(signal_signup(QString, QString, QString, QString)),this,SLOT(signup(QString, QString, QString, QString)));
    QObject::connect(signupwindow,SIGNAL(already_have_account()),this,SLOT(already_have()));
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
            sleep(10000);
       }

   }


    MainWindow* m;


};

void MainWindow::start_main_page(){
    main_page * m_p=new main_page(m);
    QObject::connect(m,SIGNAL(find_new_message(chat*)),m_p,SLOT(new_message(chat*)));
    QObject::connect(m,SIGNAL(find_new_member(chat*)),m_p,SLOT(new_member(chat*)));
    new_thread* t1=new new_thread(this);
    t1->start();
    m_p->show();

}

