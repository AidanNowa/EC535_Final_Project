#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QSignalMapper>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    //MyButton(QWidget *parent = nullptr);
    MyButton(QWidget *parent = nullptr, bool isMine = false, bool setFlag = false, bool flip = false);
    void changeflagstatus();
    void changeminestatus();
    void changeflipstatus();
    bool getflagstatus();
    bool getminestatus();
    bool getflipstatus();
    void setfliptrue();
    void setflipfalse();
protected:
    virtual void mousePressEvent(QMouseEvent *e) override;

signals:
    void leftClicked();
    void rightClicked();
private:
    bool isMine;
    bool setFlag;
    bool flip;
};

#endif // MYBUTTON_H

