#include "person.h"
#include "ui_person.h"
#include<QSqlQuery>
#include<QString>
#include<QTextCharFormat>
#include<QColor>
Person::Person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
    this->setWindowTitle("签到信息界面");
    this->setWindowIcon(QIcon("://20150821203407_tuAn5.jpeg"));
}
void Person::init(QString sno,QString sname)
{
    ui->label->setText("sno:"+sno);
    ui->label_2->setText("sname:"+sname);
    QSqlQuery qs;
    qs.exec(QString("select stime from stu_sign where sno=%1").arg(sno));
    QTextCharFormat cf;
    cf.setForeground(Qt::red);
    cf.setBackground(Qt::black);
    if(qs.size())
    {
        ui->label_3->setText("签到次数："+QString::number(qs.size()));
        while(qs.next())
        {
            ui->calendarWidget->setDateTextFormat(qs.value(0).toDate(),cf);
        }
    }
    else
    {
        ui->label_3->setText("签到次数：0");
    }
}

Person::~Person()
{
    delete ui;
}
