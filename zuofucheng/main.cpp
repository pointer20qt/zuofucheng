#include "widget.h"
#include <QApplication>
#include"login.h"
#include"widget.h"
#include<QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Login l;
    l.show();

    return a.exec();
}
