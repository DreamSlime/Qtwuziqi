#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>  //打印
#include <math.h>
#include "mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStatusBar>
#include <QLabel>
#include <QDateTime>

const int kBoardMargin = 30; // 棋盘边缘空隙
const int kRadius = 15; // 棋子半径
const int kMarkSize = 6; // 落子标记边长
const int kBlockSize = 40; // 格子的大小
const int kPosDelta = 20; // 鼠标点击的模糊距离上限

const int kAIDelay = 700; // AI下棋的思考时间

// -------------------- //

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle("wuziqi");//等于this->setWindowTitle("boss");

    //显示子窗口
    subwin.show();

    //处理子窗口的信号
    void(subwindow::*funSignal)(QString)=&subwindow::mySignal;
    connect(&subwin,funSignal, this, &MainWindow::dealsub);
    //让窗口大小不变
    resize(500, 500);

    // 设置棋盘大小
    setFixedSize(kBoardMargin * 2 + kBlockSize * kBoardSizeNum, kBoardMargin * 2 + kBlockSize * kBoardSizeNum);
    //setStyleSheet("background-color:yellow;");

    // 开启鼠标hover功能，这两句一般要设置window的
    setMouseTracking(true);
    //    centralWidget()->setMouseTracking(true);

    // 添加游戏菜单
    QMenu *gameMenu = menuBar()->addMenu(tr("Game")); // menuBar默认是存在的，直接加菜单就可以了
    QAction *actionPVP = new QAction("Person VS Person", this);
    connect(actionPVP, SIGNAL(triggered()), this, SLOT(initPVPGame()));
    gameMenu->addAction(actionPVP);

    gameMenu->addSeparator(); //添加分割线

    QAction *actionPVE = new QAction("Person VS Computer", this);
    connect(actionPVE, SIGNAL(triggered()), this, SLOT(initPVEGame()));
    gameMenu->addAction(actionPVE);

    //添加信息菜单
    QMenu *gameMenuset = menuBar()->addMenu(tr("setting")); // menuBar默认是存在的，直接加菜单就可以了
    QAction *actionPVPinf = new QAction("information(&A)", this);
    connect(actionPVPinf, SIGNAL(triggered()),this ,SLOT(showinf()));
    gameMenuset->addAction(actionPVPinf);

    //添加排行榜
    QAction *actionPVPrank = new QAction("rank(&B)", this);
    connect(actionPVPrank, SIGNAL(triggered()),this ,SLOT(showrank()));
    gameMenuset->addAction(actionPVPrank);


    //添加换背景栏
    QMenu *actionPVPback = new QMenu("background(&C)", this);
    //connect(actionPVPback, SIGNAL(triggered()),this ,SLOT(showrank()));
    gameMenuset->addMenu(actionPVPback);

    //添加退出登陆
    QAction *actionPVPexland = new QAction("Exit landing(&D)", this);
    connect(actionPVPexland, SIGNAL(triggered()),this ,SLOT(exland()));
    gameMenuset->addAction(actionPVPexland);

    //添加深木色的背景
    QAction *actionPVPdeepwood = new QAction("deepwood", this);
    connect(actionPVPdeepwood, SIGNAL(triggered()),this ,SLOT(backdeepwood()));
    actionPVPback->addAction(actionPVPdeepwood);
    //添加浅木色的背景
    QAction *actionPVPwood = new QAction("lightwood", this);
    connect(actionPVPwood, SIGNAL(triggered()),this ,SLOT(backwood()));
    actionPVPback->addAction(actionPVPwood);
    //添加灰木色的背景
    QAction *actionPVPgraywood = new QAction("graywood", this);
    connect(actionPVPgraywood, SIGNAL(triggered()),this ,SLOT(backgraywood()));
    actionPVPback->addAction(actionPVPgraywood);

    //添加橙木色的背景
    QAction *actionPVPorangewood = new QAction("orangewood", this);
    connect(actionPVPorangewood, SIGNAL(triggered()),this ,SLOT(backorangewood()));
    actionPVPback->addAction(actionPVPorangewood);

    QMenu *gameMenuoper = menuBar()->addMenu(tr("operation")); // menuBar默认是存在的，直接加菜单就可以了

    //认输
    QAction *actionPVPgiveup = new QAction("give up(&E)", this);
    connect(actionPVPgiveup, SIGNAL(triggered()),this ,SLOT(Giveup()));
    gameMenuoper->addAction(actionPVPgiveup);

    //暂停
    QAction *actionPVPpause = new QAction("pause(&F)", this);
    connect(actionPVPpause, SIGNAL(triggered()),this ,SLOT(pause()));
    gameMenuoper->addAction(actionPVPpause);

    //悔棋
    QAction *actionPVPreturn = new QAction("return(&G)", this);
    connect(actionPVPreturn, SIGNAL(triggered()),this ,SLOT(Return()));
    gameMenuoper->addAction(actionPVPreturn);

    //帮助
    //QAction *actionPVPhelp = new QAction("help(&H)", this);
    //connect(actionPVPhelp, SIGNAL(triggered()),this ,SLOT(Helpwindow()));
    //gameMenuoper->addAction(actionPVPhelp);

    //添加退出
    QAction *actionPVPexit = new QAction("exit(&I)", this);
    connect(actionPVPexit, SIGNAL(triggered()),this ,SLOT(exit()));
    gameMenuoper->addAction(actionPVPexit);


    // 开始游戏
    initGame();

     //setWindowTitle("-五子棋-");

    //状态栏

    currentTimeLabel = new QLabel; // 创建QLabel控件
    QStatusBar *sBar = statusBar();
    sBar->addWidget(new QLabel("time:",this));
    sBar->addWidget(currentTimeLabel);
    timer = new QTimer(this);
    time = new QTime(0,0,0);
    timer->start(1000); //每隔1000ms发送timeout的信号
    connect(timer, SIGNAL(timeout()),this,SLOT(time_update()));
}

void MainWindow::time_update()
{
    //time->addSecs(1);
    *time=time->addSecs(1);
    //QDateTime current_time =  new QDateTime(0,0,0);
    QString timestr = time->toString("hh:mm:ss"); //设置显示的格式
   currentTimeLabel->setText(timestr); //设置label的文本内容为时间
}

//void MainWindow::Helpwindow(){
//    helpwin.show();
//}

void MainWindow::exland(){
    this->hide();
    subwin.show();
}

void MainWindow::Return(){
    Returns=1;
}

void MainWindow::pause(){
    timer->stop();
    QMessageBox::StandardButton btnValue = QMessageBox::information(this, "pause", "The game is paused.");
    timer->start();
}

void MainWindow::backwood(){
    color=0;
}


void MainWindow::backdeepwood(){
    color=1;
}

void MainWindow::backgraywood(){
    color=2;
}

void MainWindow::backorangewood(){
    color=3;
}

void MainWindow::Giveup(){
    giveup=1;
    time->setHMS(0,0,0);
}

//退出
void MainWindow::exit(){
    this->close();
}

//显示排行榜
void MainWindow::showrank(){
    rankwin.show();
}

//显示个人信息
void MainWindow::showinf(){
    infwin.show();
    infwin.a.click();
}



void MainWindow::changeWin(){
    //子窗口显示
    subwin.show();
    //本窗口隐藏
    this->hide();
}

void MainWindow::dealsub(QString str){
    NAME = str;
    qDebug()<<NAME;
    //子窗口显示
    subwin.hide();
    //本窗口隐藏
    this->show();
    time->setHMS(0,0,0);
}

MainWindow::~MainWindow()
{
    if (game)
    {
        delete game;
        game = nullptr;
    }
}

void MainWindow::initGame()
{
    // 初始化游戏模型
    game = new GameModel;
    initPVPGame();
}

void MainWindow::initPVPGame()
{
    game_type = PERSON;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    time->setHMS(0,0,0);
    update();
}

void MainWindow::initPVEGame()
{
    game_type = BOT;
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    time->setHMS(0,0,0);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //QPainter p(this);
    QPainter p;  //创建画家对象
    p.begin(this); //指定当前窗口为绘图设备

    //绘图操作
    //画背景图
    if(color == 0)
    p.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=3967820435,4109070133&fm=26&gp=0.jpg"));

    if(color == 1)
    p.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=867276353,2609607622&fm=72.jpg"));

    if(color == 2)
    p.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=1985406695,1258431003&fm=11&gp=0_WPS图片.jpg"));

    if(color == 3)
    p.drawPixmap(0,0,width(),height(), QPixmap("../Image/u=3606751862,1869919184&fm=26&gp=0.jpg"));

    QPainter painter(this);
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
//    QPen pen; // 调整线条宽度
//    pen.setWidth(2);
//    painter.setPen(pen);
    for (int i = 0; i < kBoardSizeNum + 1; i++)
    {
        painter.drawLine(kBoardMargin + kBlockSize * i, kBoardMargin, kBoardMargin + kBlockSize * i, size().height() - kBoardMargin);
        painter.drawLine(kBoardMargin, kBoardMargin + kBlockSize * i, size().width() - kBoardMargin, kBoardMargin + kBlockSize * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记(防止鼠标出框越界)
    if (clickPosRow > 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < kBoardSizeNum &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if (game->playerFlag)
            brush.setColor(Qt::white);
        else
            brush.setColor(Qt::black);
        painter.setBrush(brush);
        painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
    }
    if(Returns==1){
        game->gameMapVec[a[nows][0]][a[nows][1]]=0;
        nows--;
        Returns=0;
    }
    // 绘制棋子
    for (int i = 0; i < kBoardSizeNum; i++)
        for (int j = 0; j < kBoardSizeNum; j++)
        {
            if (game->gameMapVec[i][j] == 1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
            else if (game->gameMapVec[i][j] == -1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
        }

    if(giveup == 1){
        QString str = "black player";
        giveup = 0;
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + " win!");
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
            //获得数据库中win，lise的值
            QString  win;
            QString  lose;
            QString sq=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
            QSqlQuery sqlquery=QSqlQuery(db);
            sqlquery.exec(sq);
            while (sqlquery.next())
            {
                    win.append(sqlquery.value(3).toString());
            }

            QString sq1=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
            QSqlQuery sqlquery1=QSqlQuery(db);
            sqlquery1.exec(sq1);
            while (sqlquery1.next())
            {
                    lose.append(sqlquery1.value(4).toString());
            }

            //qDebug()<<win;
            qDebug()<<lose;
            //默认用户为白棋，输
            if(str == "black player"){
            int newlose = lose.toInt()+1;
            QSqlQuery query;
            query.prepare("update wuziqi_info set lose=? where handle=?");
            query.addBindValue(newlose);
            query.addBindValue(NAME);
            query.exec();
            }
            // 重置游戏状态，否则容易死循环
            if (btnValue == QMessageBox::Ok)
            {
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }
    }
    else{
    if (clickPosRow > 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < kBoardSizeNum &&
        (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
            game->gameMapVec[clickPosRow][clickPosCol] == -1))
    {
        if (game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {
            qDebug() << "win";
            game->gameStatus = WIN;
            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "white player";
            else if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                str = "black player";
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "congratulations", str + " win!");
              time->setHMS(0,0,0);
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
                //获得数据库中win，lise的值
                QString  win;
                QString  lose;
                QString sq=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
                QSqlQuery sqlquery=QSqlQuery(db);
                sqlquery.exec(sq);
                while (sqlquery.next())
                {
                        win.append(sqlquery.value(3).toString());
                }

                QString sq1=QStringLiteral("select *from wuziqi_info where handle='%1' ").arg(NAME);
                QSqlQuery sqlquery1=QSqlQuery(db);
                sqlquery1.exec(sq1);
                while (sqlquery1.next())
                {
                        lose.append(sqlquery1.value(4).toString());
                }

                //qDebug()<<win;
                //qDebug()<<lose;
                //默认用户为白棋，赢
                if(str == "white player"){
                int newwin = win.toInt()+1;
                QSqlQuery query;
                query.prepare("update wuziqi_info set win=? where handle=?");
                query.addBindValue(newwin);
                query.addBindValue(NAME);
                query.exec();
            }
                //默认用户为白棋，输
                if(str == "black player"){
                int newlose = lose.toInt()+1;
                QSqlQuery query;
                query.prepare("update wuziqi_info set lose=? where handle=?");
                query.addBindValue(newlose);
                query.addBindValue(NAME);
                query.exec();
            }
            // 重置游戏状态，否则容易死循环
            if (btnValue == QMessageBox::Ok)
            {
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }
        }
}


    // 判断死局
    if (game->isDeadGame())
    {
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
        if (btnValue == QMessageBox::Ok)
        {
            game->startGame(game_type);
            game->gameStatus = PLAYING;
        }

    }
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->x();
    int y = event->y();

    // 棋盘边缘不能落子
    if (x >= kBoardMargin + kBlockSize / 2 &&
            x < size().width() - kBoardMargin &&
            y >= kBoardMargin + kBlockSize / 2 &&
            y < size().height()- kBoardMargin)
    {
        // 获取最近的左上角的点
        int col = x / kBlockSize;
        int row = y / kBlockSize;

        int leftTopPosX = kBoardMargin + kBlockSize * col;
        int leftTopPosY = kBoardMargin + kBlockSize * row;

        // 根据距离算出合适的点击位置,一共四个点，根据半径距离选最近的
        clickPosRow = -1; // 初始化最终的值
        clickPosCol = -1;
        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }

    // 存了坐标后也要重绘
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // 人下棋，并且不能抢机器的棋
    if (!(game_type == BOT && !game->playerFlag))
    {
        chessOneByPerson();
        // 如果是人机模式，需要调用AI下棋
        if (game->gameType == BOT && !game->playerFlag)
        {
            // 用定时器做一个延迟
            QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));
        }
    }

}

void MainWindow::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才下子，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        nows++;
        game->actionByPerson(clickPosRow, clickPosCol);
        a[nows][0]=clickPosRow;
        a[nows][1]=clickPosCol;
        // 重绘
        update();
    }
}

void MainWindow::chessOneByAI()
{
    game->actionByAI(clickPosRow, clickPosCol);
    update();
}
