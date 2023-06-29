#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include <QMainWindow>
#include"main_user.h"
#include<QWidgetItem>
#include<QListWidgetItem>
namespace Ui {
class main_page;
}

class main_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit main_page(main_user*,QWidget *parent = nullptr);
    ~main_page();

    void set_member_list(QVector<chat*>);
    void set_messages_graphicview(QVector<Message>);

public slots:
    void new_message();
    //when we have a new message
    //refresh memberlist and maybe message graphicview
    //this slot connects to mainuser signal(find_new_message)


private slots:
    void on_all_button_clicked();

    void on_member_list_itemClicked(QListWidgetItem *item);

private:
    main_user* m;
    chat* clicked_chat;
    Ui::main_page *ui;
};

#endif // MAIN_PAGE_H
