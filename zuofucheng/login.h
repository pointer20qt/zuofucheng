#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QString>
#include<QSqlDatabase>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    QString pwd;
    QSqlDatabase db;
private:
    Ui::Login *ui;
};

#endif // LOGIN_H
