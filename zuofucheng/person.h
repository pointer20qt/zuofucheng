#ifndef PERSON_H
#define PERSON_H

#include <QWidget>
#include<QString>
namespace Ui {
class Person;
}

class Person : public QWidget
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = 0);
    ~Person();
    void init(QString sno,QString sname);
private:
    Ui::Person *ui;
};

#endif // PERSON_H
