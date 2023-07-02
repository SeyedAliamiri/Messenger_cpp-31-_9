#ifndef JOIN_CHANNEL_GROUP_H
#define JOIN_CHANNEL_GROUP_H

#include <QDialog>

namespace Ui {
class join_channel_group;
}

class join_channel_group : public QDialog
{
    Q_OBJECT

public:
    explicit join_channel_group(bool channel1_group0,QWidget *parent = nullptr);
    ~join_channel_group();

private slots:
    void on_buttonBox_accepted();

signals:
    void signal_join(QString);

private:
    Ui::join_channel_group *ui;
};

#endif // JOIN_CHANNEL_GROUP_H
