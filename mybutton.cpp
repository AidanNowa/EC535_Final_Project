#include "mybutton.h"
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QSignalMapper>
#include <QMouseEvent>

MyButton::MyButton(QWidget *parent, bool isMine, bool setFlag, bool flip)
    : QPushButton(parent)
{
    this->isMine = isMine;
    this->setFlag = setFlag;
    this->flip = flip;
}

bool MyButton::getflagstatus(){
    return this->setFlag;
}
bool MyButton::getminestatus(){
    return this->isMine;
}
bool MyButton::getflipstatus(){
    return this->flip;
}
void MyButton::changeflagstatus(){
    this->setFlag = !this->setFlag;
}
void MyButton::changeminestatus(){
    this->isMine = !this->isMine;
}
void MyButton::changeflipstatus(){
    this->flip = !this->flip;
}

void MyButton::setfliptrue(){
    this->flip = true;
}

void MyButton::setflipfalse(){
    this->flip = false;
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        emit leftClicked();
    }
    else if (e->button() == Qt::RightButton)
    {
        emit rightClicked();
    }

    QPushButton::mousePressEvent(e);
}
