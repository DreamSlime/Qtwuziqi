#include "registerwindow.h"
#include <qstring.h>
#include <QLabel>
#include <QLineEdit.h>
#include <QDebug>
#include <QMessageBox>
#include <QVariantList>
#include <QSqlDatabase>
#include <qsqltablemodel.h>
#include <qsqlquery.h>
#include <qlabel.h>
#include <QPainter>
#include <QPen>
#include <QBrush>

registerwindow::registerwindow(QWidget *parent) : QWidget(parent)
{

    setWindowTitle("注册界面");
    d.setParent(this);
    d.setText("注册");
    d.move(300,300);
    resize(500, 500);
    connect(&d, &QPushButton::clicked, this, &registerwindow::sendregitslot);

    e.setParent(this);
    e.setText("返回登陆");
    e.move(400,300);
    connect(&e, &QPushButton::clicked, this, &registerwindow::sendreturnslot);

    pNormalLineEdit1->setPlaceholderText("handle");
    pPasswordLineEdit1->setPlaceholderText("Password");
    pPasswordLineEdit2->setPlaceholderText("Password");

    pNormalLineEdit1->move(150,100);
    pPasswordLineEdit1->move(150,125);
    pPasswordLineEdit2->move(150,150);

    // 设置显示效果
    pNormalLineEdit1->setEchoMode(QLineEdit::Normal);
    pPasswordLineEdit1->setEchoMode(QLineEdit::Password);
    pPasswordLineEdit2->setEchoMode(QLineEdit::Password);

    pNormalLineEdit2->setPlaceholderText("name");
    pNormalLineEdit3->setPlaceholderText("sex");

    pNormalLineEdit2->move(150,175);
    pNormalLineEdit3->move(150,200);

    // 设置显示效果
    pNormalLineEdit2->setEchoMode(QLineEdit::Normal);
    pNormalLineEdit3->setEchoMode(QLineEdit::Normal);

    QString data6;
    data6="账号:";
    QLabel *label6 = new QLabel(this);
    label6->setText(QString(data6));
    label6->move(50,100);

    QString data7;
    data7="密码:";
    QLabel *label7 = new QLabel(this);
    label7->setText(QString(data7));
    label7->move(50,128);

    QString data8;
    data8="重新确认密码:";
    QLabel *label8 = new QLabel(this);
    label8->setText(QString(data8));
    label8->move(50,154);

    QString data9;
    data9="姓名:";
    QLabel *label9 = new QLabel(this);
    label9->setText(QString(data9));
    label9->move(50,180);

    QString data10;
    data10="性别(men/women):";
    QLabel *label10 = new QLabel(this);
    label10->setText(QString(data10));
    label10->move(27,205);
}

void  registerwindow::sendreturnslot(){
    emit regitSignal();
}

void registerwindow::sendregitslot(){
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

    QString handle=pNormalLineEdit1->text();
    QString passwd1=pPasswordLineEdit1->text();
    QString passwd2=pPasswordLineEdit2->text();
    QString name=pNormalLineEdit2->text();
    QString sex=pNormalLineEdit3->text();

    if(passwd1!=passwd2){
        QMessageBox::information(this, "warning","密码不一致.");
        pNormalLineEdit1->clear();
        pPasswordLineEdit1->clear();
        pPasswordLineEdit2->clear();
    }
    else if (handle== '\0' || passwd1=='\0'){
        QMessageBox::information(this, "warning","密码/账号不能为空.");
        pNormalLineEdit1->clear();
        pPasswordLineEdit1->clear();
        pPasswordLineEdit2->clear();
    }
    else{
        QString str = QString("select *from wuziqi_info where handle = '%1'").arg(handle);
        QSqlQuery query;
        query.exec(str);
        int o=0;

        while (query.next()){
           o=1;
        }

    if(o==1){
        QMessageBox::information(this, "Warning", " Account already exists ");
        pNormalLineEdit1->clear();
        pPasswordLineEdit1->clear();
        pPasswordLineEdit2->clear();
    }
    else{
        QMessageBox::information(this, "login", " login was successful ");
        QString str=QString("insert into wuziqi_info(handle, passwd,  win, lose, name, sex) values('%1','%2', 0 , 0 ,'%3','%4')").arg(handle).arg(passwd1).arg(name).arg(sex);
        QSqlQuery query;
        query.exec(str);
        //textEdit->setText("插入成功");
        pNormalLineEdit1->clear();
        pPasswordLineEdit1->clear();
        pPasswordLineEdit2->clear();
         emit regitSignal();
    }
  }
}

void registerwindow::paintEvent(QPaintEvent *){
    //QPainter p(this);
    QPainter p;  //创建画家对象
    p.begin(this); //指定当前窗口为绘图设备

    //绘图操作
    //画背景图
    p.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=1869757711,2217152015&fm=26&gp=0.jpg"));

}
