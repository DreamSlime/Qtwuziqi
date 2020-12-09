#ifndef SUBWINDOW_H
#define SUBWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <qlineedit.h>
#include "registerwindow.h"
#include <QPaintEvent>

class subwindow : public QWidget
{
    Q_OBJECT
public:
    explicit subwindow(QWidget *parent = nullptr);
     void sendSlot();
     void subwindow::on_pushButton_2_clicked();
     QLineEdit *pNormalLineEdit = new QLineEdit(this);
     QLineEdit *pPasswordLineEdit = new QLineEdit(this);
     void changwin();
     void dealSlot();


protected:
    //重写绘图事件
    //如果在窗口绘图，必须在绘图事件里实现
    //绘图事件内部自动调用，窗口需要重绘的时候（状态改变）
    void paintEvent(QPaintEvent *);

signals:
     /*信号必须有signals关键字来声明
      * 信号没有返回值，但可以有参数
      * 信号就是函数的声明，只需声明，无需定义
     */
     void mySignal(QString);
public slots:

private:
    QPushButton b;
    QPushButton c;

    registerwindow regist;
};

#endif // SUBWINDOW_H
