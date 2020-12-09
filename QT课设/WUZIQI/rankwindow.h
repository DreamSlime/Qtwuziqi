#ifndef TANKWINDOW_H
#define TANKWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSqlTableModel>
#include <QTableView>
#include <QPaintEvent>

class rankwindow : public QWidget
{
    Q_OBJECT
public:
    explicit rankwindow(QWidget *parent = nullptr);

signals:

public slots:

protected:
    //重写绘图事件
    //如果在窗口绘图，必须在绘图事件里实现
    //绘图事件内部自动调用，窗口需要重绘的时候（状态改变）
    void paintEvent(QPaintEvent *);
};

#endif // TANKWINDOW_H
