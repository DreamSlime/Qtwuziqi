#include "rankwindow.h"
#include <QDebug>
#include <QPushButton>
#include <subwindow.h>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include<QTimer>
#include <QLabel>
#include <QSqlTableModel>
#include <QTableView>
#include <QPainter>
#include <QPen>
rankwindow::rankwindow(QWidget *parent) : QWidget(parent)
{

}


void rankwindow::paintEvent(QPaintEvent *){

    QPainter p;  //创建画家对象
    p.begin(this); //指定当前窗口为绘图设备
    //绘图操作
    //画背景图
    p.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=4069830077,209421225&fm=26&gp=0.jpg"));


}
