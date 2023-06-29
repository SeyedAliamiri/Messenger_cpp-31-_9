#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QMainWindow>

namespace Ui {
class sign_in;
}

class sign_in : public QMainWindow
{
    Q_OBJECT

public:
    explicit sign_in(QWidget *parent = nullptr);
    ~sign_in();

private slots:
    void on_password_2_lineedit_textChanged(const QString &arg1);

    void on_sign_in_button_clicked();

    void on_alreadyhaveacount_clicked();

private:
    Ui::sign_in *ui;
};

#endif // SIGN_IN_H
