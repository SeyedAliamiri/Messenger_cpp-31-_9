#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QMainWindow>
#include"main_user.h"
#include <QHBoxLayout>
#include <QTextBrowser>
#include<QWidgetItem>
#include<QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class main_page; }
QT_END_NAMESPACE

class main_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_page(main_user*,QWidget *parent = nullptr);
    ~main_page();

    void set_member_list(QVector<chat*>);
    void set_messages_graphicview(QVector<Message>);




private slots:
     void new_message(chat*);

     void new_member(chat*);
    void on_all_button_clicked();

    void on_member_list_itemClicked(QListWidgetItem *item);

    void on_group_button_clicked();

    void on_channel_button_clicked();

    void on_send_button_clicked();

    void on_users_button_clicked();

private:
    main_user* m;
    chat* clicked_chat;
    int member_list_type_id;
    //0=nothing 1=user 2=channels 3=groups 4=all
    Ui::main_page *ui;
    QVector<QHBoxLayout*> mesageslayout;
    QVector<QTextBrowser*> mesagestext;
    static QString messageto_html(Message message);
};

#endif // MAIN_PAGE_H
