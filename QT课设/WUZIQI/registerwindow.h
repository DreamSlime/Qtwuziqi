#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <qlineedit.h>

class registerwindow : public QWidget
{
    Q_OBJECT
public:
    explicit registerwindow(QWidget *parent = nullptr);
    void sendregitslot();
    void sendreturnslot();
    QLineEdit *pNormalLineEdit1 = new QLineEdit(this);
    QLineEdit *pNormalLineEdit2 = new QLineEdit(this);
    QLineEdit *pNormalLineEdit3 = new QLineEdit(this);
    QLineEdit *pPasswordLineEdit1 = new QLineEdit(this);
    QLineEdit *pPasswordLineEdit2 = new QLineEdit(this);

protected:
    //重写绘图事件
    //如果在窗口绘图，必须在绘图事件里实现
    //绘图事件内部自动调用，窗口需要重绘的时候（状态改变）
    void paintEvent(QPaintEvent *);


signals:
        void regitSignal();

public slots:

private:
    QPushButton d;
    QPushButton e;
};

#endif // REGISTERWINDOW_H
