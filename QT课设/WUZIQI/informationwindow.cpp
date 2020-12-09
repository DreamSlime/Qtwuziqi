#include "informationwindow.h"
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

informationwindow::informationwindow(QWidget *parent) : QWidget(parent)
{
    a.setParent(this);
    a.setText("clike");
   connect(&a,&QPushButton::clicked,this,&informationwindow::cout);
    a.move(100,100);

    /*QTimer *timer=new QTimer;
        connect(timer, &QTimer::timeout, this, [&](){
            //5秒调用一次，想干啥都行
            //假设按钮是pushButton
            a.click();
        });
        timer->start(100);
*/
    a.hide();
    this->setWindowTitle("Personal Information");
    resize(500,500);
}

void informationwindow::cout(){

    qDebug()<<QSqlDatabase::drivers();
    //添加MYSQL数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL"); //数据库对象
    //连接数据库
    db.setHostName("127.0.0.1"); //数据库服务器IP
    db.setUserName("root"); //数据库用户名
    db.setPassword("holdworld000312"); //数据库密码
    db.setDatabaseName("slimes"); //使用哪个数据库

    if(!db.open()){
        QMessageBox::information(this, "连接结果", "连接数据库失败!");
        return;
    }


    QString sq=QStringLiteral("select *from wuziqi_user where id=1");
    QSqlQuery sqlquery=QSqlQuery(db);
    sqlquery.exec(sq);
    NAME = "";
    while (sqlquery.next())
    {
            NAME.append(sqlquery.value(1).toString());
    }

    win = "";
    QString sq5=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
    QSqlQuery sqlquery5=QSqlQuery(db);
    sqlquery5.exec(sq5);
    while (sqlquery5.next())
    {
            win.append(sqlquery5.value(3).toString());
    }

    handle = "";
    QString sq1=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
    QSqlQuery sqlquery1=QSqlQuery(db);
    sqlquery1.exec(sq1);
    while (sqlquery1.next())
    {
            handle.append(sqlquery1.value(1).toString());
    }

    lose = "";
    QString sq2=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
    QSqlQuery sqlquery2=QSqlQuery(db);
    sqlquery2.exec(sq2);
    while (sqlquery2.next())
    {
            lose.append(sqlquery2.value(4).toString());
    }

    name = "";
    QString sq3=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
    QSqlQuery sqlquery3=QSqlQuery(db);
    sqlquery3.exec(sq3);
    while (sqlquery3.next())
    {
           name.append(sqlquery3.value(5).toString());
    }

    sex = "";
    QString sq4=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
    QSqlQuery sqlquery4=QSqlQuery(db);
    sqlquery4.exec(sq4);
    while (sqlquery4.next())
    {
           sex.append(sqlquery4.value(6).toString());
    }
    resize(500,500);



    qDebug()<< NAME<<handle<<win<<lose<<name<<sex;

}

void informationwindow::paintEvent(QPaintEvent *){

    QPainter p2;  //创建画家对象
    p2.begin(this); //指定当前窗口为绘图设备
    //绘图操作
    //画背景图
    p2.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=3720865353,2633372586&fm=26&gp=0.jpg"));
    //QPainter p(this);
   if( sex == "men"){
    QPainter p;  //创建画家对象
    p.begin(this); //指定当前窗口为绘图设备
    //绘图操作
    //画背景图
    p.drawPixmap(100,100,100,100, QPixmap("../Image/7D016817BF7BEE8D56116FCBA333DBFB.jpg"));
    }
   if( sex == "women"){
    QPainter p1;  //创建画家对象
    p1.begin(this);//指定当前窗口为绘图设备
    //绘图操作
    //画背景图
    p1.drawPixmap(100,100,100,100, QPixmap("../Image/776CC876C0FAD440626034DE13CD5866.jpg"));
   }
}


