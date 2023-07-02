#ifndef CREATE_CHANNEL_GROUP_H
#define CREATE_CHANNEL_GROUP_H

#include <QDialog>

namespace Ui {
class create_channel_group;
}

class create_channel_group : public QDialog
{
    Q_OBJECT

public:
    explicit create_channel_group(bool channel1_group0, QWidget *parent = nullptr);
    ~create_channel_group();

private slots:
    void on_buttonBox_accepted();
signals:
    void signal_creat(QString, QString);

private:
    Ui::create_channel_group *ui;
};

#endif // CREATE_CHANNEL_GROUP_H
