#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMouseEvent>
#include<QString>
#include<QSqlDatabase>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0,QString user=NULL);
    ~Widget();
    void addcombox();
    void show_stu(QString text,QString user);
    void show_stu_sno(QString sno);
    QString user;
    QString sno;
    QString stu_class="全部";
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
