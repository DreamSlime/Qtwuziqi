#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSqlTableModel>
#include <QTableView>
#include <QPaintEvent>

class informationwindow : public QWidget
{
    Q_OBJECT
public:
    explicit informationwindow(QWidget *parent = nullptr);
    QPushButton a;
    void cout();
    QString NAME;

    QString  win;
    QString  lose;
    QString  name;
    QString  handle;
    QString  sex;

signals:

public slots:

private:
    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);
    QLabel *label3 = new QLabel(this);
    QLabel *label4 = new QLabel(this);
    QLabel *label5 = new QLabel(this);
    QLabel *label6 = new QLabel(this);
protected:
    //重写绘图事件
    //如果在窗口绘图，必须在绘图事件里实现
    //绘图事件内部自动调用，窗口需要重绘的时候（状态改变）
    void paintEvent(QPaintEvent *);

};

#endif // INFORMATIONWINDOW_H
