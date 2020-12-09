#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameModel.h"
#include <QPushButton>
#include "subwindow.h" //子窗口头文件
#include "informationwindow.h"
#include "rankwindow.h"
#include <Qpair>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton b3;
    //void mySlot();
    void changeWin();
    void dealsub(QString);
    QString NAME;
    int color=0;
    int giveup=0;
    int Returns=0;

protected:
    // 绘制
    void paintEvent(QPaintEvent *event);
    // 监听鼠标移动情况，方便落子
    void mouseMoveEvent(QMouseEvent *event);
    // 实际落子
    void mouseReleaseEvent(QMouseEvent *event);



private:
    GameModel *game; // 游戏指针
    GameType game_type; // 存储游戏类型
    int clickPosRow, clickPosCol; // 存储将点击的位置
    void initGame();
    void checkGame(int y, int x);

    subwindow subwin; //子窗口
    informationwindow infwin;
    rankwindow rankwin;
    QLabel *currentTimeLabel; // 先创建一个QLabel对象
    QTime *time;
    QTimer *timer;
    int a[1000][2];
    int nows=0;

private slots:
    void chessOneByPerson(); // 人执行
    void chessOneByAI(); // AI下棋

    void initPVPGame();
    void initPVEGame();
    void showinf();
    void showrank();
    void exit();
    void backdeepwood();
    void backwood();
    void backgraywood();
    void backorangewood();
    void Giveup();
    void pause();
    void Return();
    void exland();
    //void Helpwindow();
    void time_update(); //时间更新槽函数，状态栏显示时间

signals:
     /*信号必须有signals关键字来声明
      * 信号没有返回值，但可以有参数
      * 信号就是函数的声明，只需声明，无需定义
     */
     void mySignal(QString);

};

#endif // MAINWINDOW_H
