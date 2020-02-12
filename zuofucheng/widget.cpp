#include "widget.h"
#include "ui_widget.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QCheckBox>
#include<QDateTime>
#include<QTableWidgetItem>
#include<QString>
#include<QComboBox>
#include<QPushButton>
#include<QMessageBox>
#include"person.h"
#include"login.h"
#include<QIcon>
Widget::Widget(QWidget *parent,QString user) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("信息界面");
    this->setWindowIcon(QIcon("://20150821203407_tuAn5.jpeg"));
    ui->comboBox->addItem("全部");
    addcombox();
    QSqlQuery sq;
    show_stu("全部",user);
    qDebug()<<user;
    if(sq.exec("select * from student"))
    {
        connect(ui->comboBox,QComboBox::currentTextChanged,ui->tableWidget,[=](QString text){
              show_stu(text,user);
        });
        connect(ui->pushButton,QPushButton::clicked,ui->tableWidget,[=](){
              sno=ui->lineEdit->text();
              show_stu_sno(sno);
        });
        Person *p=new Person();
        connect(ui->tableWidget,QTableWidget::cellDoubleClicked,p,[=](int r,int c){
            p->show();
            p->init(ui->tableWidget->item(r,0)->text(),ui->tableWidget->item(r,1)->text());
        });
    }



}

void Widget::addcombox()
{
    QSqlQuery sq;
    if(sq.exec("select distinct class from student"))
    {
        while(sq.next())
        {
            ui->comboBox->addItem(sq.value(0).toString());
        }
    }
}
void Widget::show_stu_sno(QString sno)
{
    QSqlQuery sq;
    sq.exec(QString("select * from student where sno=%1").arg(sno));
    if(sq.size()==1)
    {
        int i=0;
        sq.next();
        ui->tableWidget->setRowCount(1);
        QCheckBox *c=new QCheckBox();
        QString s=sq.value(0).toString();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(s));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(sq.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(sq.value(2).toString()));
        ui->tableWidget->setCellWidget(i,3,c);
        QSqlQuery sign;
        sign.exec(QString("select * from stu_sign where sno=%1 and day(stime)=day(now()) order by stime desc").arg(s));
        sign.next();
        if(sign.size())
        {
            c->setText("已签到");
            c->setDisabled(true);
            c->setChecked(true);
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(sign.value(1).toString()));
        }
        connect(c,QCheckBox::clicked,[=]()
        {
            c->setText("已签到");
            c->setDisabled(true);
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));
            QSqlQuery iq;
            iq.exec(QString("insert into stu_sign values(%1,now())").arg(s));
        });
    }
    else
    {
        QMessageBox::warning(this,"warn","输入错误");
    }

}

void Widget::show_stu(QString text,QString user)
{
    QSqlQuery sq;
    if(text=="全部")
    {
        sq.exec("select * from student");
    }
    else
    {
        sq.exec(QString("select * from student where class=%1").arg(text));
    }
    int i=0;

    while(sq.next())
    {
        ui->tableWidget->setRowCount(sq.size());
        QCheckBox *c=new QCheckBox();
        QString s=sq.value(0).toString();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(s));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(sq.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(sq.value(2).toString()));
        ui->tableWidget->setCellWidget(i,3,c);
        QSqlQuery sign;
        sign.exec(QString("select * from stu_sign where sno=%1 and day(stime)=day(now()) order by stime desc").arg(s));
        sign.next();
        c->setDisabled(true);
        c->setText("未签到");
        if(user==ui->tableWidget->item(i,0)->text())
        {
            c->setDisabled(false);
        }
        if(sign.size())
        {
            c->setText("已签到");
            c->setDisabled(true);
            c->setChecked(true);
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(sign.value(1).toString()));
        }
        connect(c,QCheckBox::clicked,[=]()
        {
            c->setText("已签到");
            c->setDisabled(true);
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));
            QSqlQuery iq;
            iq.exec(QString("insert into stu_sign values(%1,now())").arg(s));
        });
        i++;
    }
}






Widget::~Widget()
{
    delete ui;
}
