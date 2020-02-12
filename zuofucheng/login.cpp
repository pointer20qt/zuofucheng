#include "login.h"
#include "ui_login.h"
#include<QPushButton>
#include"widget.h"
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QString>
#include<QMessageBox>
#include<QDebug>
#include"widget.h"
#include"register.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("登录界面");
    this->setWindowIcon(QIcon("://20150821203407_tuAn5.jpeg"));
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("20_sign");
    db.setPassword("123456");
    db.setUserName("root");
    db.open();
    connect(ui->pushButton,QPushButton::clicked,[=](){
        QSqlQuery qs;
        qs.exec(QString("select * from stu_user where s_user=%1 and s_pwd=%2").arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text()));
        qs.size();
        if(qs.size()&&ui->lineEdit->text()!=NULL&&ui->lineEdit_2->text()!=NULL)
        {

            this->hide();
            qs.next();
            Widget* w=new Widget(parent,qs.value(0).toString());
            w->show();
        }
        else
        {
            QMessageBox::warning(this,"warn","账号或密码错误");
        }
    });
    connect(ui->pushButton_2,QPushButton::clicked,[=](){
        Register *r=new Register();
        r->show();


    });

}


Login::~Login()
{
    delete ui;
}
