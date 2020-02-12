#include "register.h"
#include "ui_register.h"
#include<QSqlQuery>
#include<QString>
#include<QMessageBox>
#include<QPushButton>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowTitle("注册界面");
    this->setWindowIcon(QIcon("://20150821203407_tuAn5.jpeg"));
    connect(ui->pushButton,QPushButton::clicked,[=](){
        QSqlQuery qs;
        qs.exec(QString("select * from stu_user where s_user=%1").arg(ui->lineEdit->text()));
        if(qs.size())
        {
            QMessageBox::warning(this,"warn","账号已存在");
        }
        else
        {
            qs.exec(QString("insert into stu_user values(%1,%2)").arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text()));
            qs.exec(QString("insert into student values(%1,%2,%3)").arg(ui->lineEdit->text()).arg(ui->lineEdit_3->text()).arg(ui->lineEdit_4->text()));
            QMessageBox::warning(this,"warn","注册成功");
        }
    });
    connect(ui->pushButton_2,QPushButton::clicked,[=](){
        this->close();
    });

}

Register::~Register()
{
    delete ui;
}
