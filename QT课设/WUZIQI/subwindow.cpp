#include "subwindow.h"
#include <qstring.h>
#include <QLabel>
#include <QLineEdit.h>
#include <QDebug>
#include <QMessageBox>
#include <QVariantList>
#include <QSqlDatabase>
#include <qsqltablemodel.h>
#include <qfont.h>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <qsqlquery.h>

subwindow::subwindow(QWidget *parent) : QWidget(parent)
{

    QString data4;
    data4="Handle/Email:";
    QLabel *label4 = new QLabel(this);
    label4->setText(QString(data4));
    label4->move(15,255);

    QString data5;
    data5="Password:";
    QLabel *label5 = new QLabel(this);
    label5->setText(QString(data5));
    label5->move(15,293);

    pNormalLineEdit->setPlaceholderText("Normal");
    pPasswordLineEdit->setPlaceholderText("Password");

    pNormalLineEdit->move(125,250);
    pPasswordLineEdit->move(125,290);

    // 设置显示效果
    pNormalLineEdit->setEchoMode(QLineEdit::Normal);
    pPasswordLineEdit->setEchoMode(QLineEdit::Password);


    this->setWindowTitle("登陆界面");
    b.setParent(this);
    b.setText("Login");
    b.move(320,300);
    connect(&b, &QPushButton::clicked, this, &subwindow::sendSlot);

    c.setParent(this);
    c.setText("Register");
    c.move(320,350);

    connect(&c, &QPushButton::released, this, &subwindow::changwin);

    QString data;
    data="抵制不良游戏，拒绝盗版游戏；";
    QLabel *label = new QLabel(this);
    label->setText(QString(data));
    label->move(25,350);

    QString data1;
    data1="注意自我保护，谨防受骗上当；";
    QLabel *label1 = new QLabel(this);
    label1->setText(QString(data1));
    label1->move(25,375);

    QString data2;
    data2="适度游戏益脑，沉迷游戏伤身；";
    QLabel *label2 = new QLabel(this);
    label2->setText(QString(data2));
    label2->move(25,400);

    QString data3;
    data3="合理安排时间，享受健康生活；";
    QLabel *label3 = new QLabel(this);
    label3->setText(QString(data3));
    label3->move(25,425);


    //让窗口大小不变
    resize(500, 460);


    //处理registerwindow的信号
    connect(&regist,&registerwindow::regitSignal, this ,&subwindow::dealSlot);

}

void subwindow::dealSlot(){
    //registerwindow隐藏
    regist.hide();
    //subwindow显示
    this->show();
}

void subwindow::changwin(){
    //registerwindow显示
    regist.show();
    //subwindow隐藏
    this->hide();
}


void subwindow::sendSlot()
{
    //打印QT支持的数据库驱动
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

    QString handle=pNormalLineEdit->text();
    QString passwd=pPasswordLineEdit->text();

    QSqlTableModel model;
    model.setTable("wuziqi_info");
    model.setFilter(tr("handle = '%1' and passwd = '%2'").arg(handle).arg(passwd));
    model.select();

    if(model.rowCount() == 1){
        QString NAME = handle;
        // 表示密码验证正确，登陆成功
        // ...... 显示登录后的状态
        QMessageBox::information(this, "Login", "登录成功!");

        QSqlQuery query1;
             query1.prepare("DELETE  From wuziqi_user where id=1");
              if(!query1.exec())//如果成功执行则返回1，未执行则为零
                 qDebug()<<"fail";

        QString sex = "";
        QString sq4=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
        QSqlQuery sqlquery4=QSqlQuery(db);
        sqlquery4.exec(sq4);
        while (sqlquery4.next())
        {
               sex.append(sqlquery4.value(6).toString());
        }
        QString str=QString("insert into wuziqi_user(id,handle,sex) values(1,'%1','%2')").arg(handle).arg(sex);
        QSqlQuery query;
        query.exec(str);
        emit mySignal(NAME);
    }
    else{
        QMessageBox::information(this, "Warning", "用户名或密码错误，请重新输入!");
        pNormalLineEdit->clear();
        pPasswordLineEdit->clear();
    }
}

void subwindow::on_pushButton_2_clicked()
{
    close();
}

void subwindow::paintEvent(QPaintEvent *){
    //QPainter p(this);
    QPainter p;  //创建画家对象
    p.begin(this); //指定当前窗口为绘图设备
    //绘图操作
    //画背景图
    p.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=4105832563,1730732419&fm=26&gp=0_WPS图片.jpg"));

    QPainter p1;  //创建画家对象
    p1.begin(this);//指定当前窗口为绘图设备
    //绘图操作
    //画背景图
    p1.drawPixmap(0,-30,250,300, QPixmap("../Image/614356656556334208.png"));
}
