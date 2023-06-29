#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"chat.h"
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

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
                QMessageBox::information(signupwindow, "Success", message, QMessageBox::Ok);

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

                token = jsonObj.value("token").toString();                                      //now what to do with token???
            }
            else{
                QMessageBox::critical(loginwindow, "Failure", message, QMessageBox::Ok);
            }
        }
    });
}

