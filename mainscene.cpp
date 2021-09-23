#include "mainscene.h"
#include "config.h"
#include "gameover.h"

#include <QIcon>
#include <QPainter>
#include <ctime>
#include <QKeyEvent>
#include <QDebug>
#include <QPushButton>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    srand((unsigned int)time(NULL)); //随机数种子
    this->setFocus();
    setButton();
    initScene();
}

MainScene::~MainScene()
{

}

void MainScene::initScene()
{

    //设置窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置窗口标题
    setWindowTitle(GAME_TITLE);
    //setWindowIcon(QIcon(GAME_ICON));
    setWindowIcon(QIcon(GAME_SQARE));
    //设置时间间隔


    //最后用按钮实现
    //playGame();
    connect(&m_Timer,&QTimer::timeout,[=](){
        updatePosition();
        update();
    });
}

void MainScene::playGame()
{

    //从新设置整个游戏
    interval = GAME_INTERVAL;
    m_Timer.setInterval(interval);

    setScore(0);

    m_Timer.start();
    //清空整个游戏
    clearBack();
    clearShape();
    creatShape( rand() % 4 );
    tpos_x = 8;
    tpos_y = 0;
    update();


//    connect(&m_Timer,&QTimer::timeout,[=](){
//        updatePosition();
//        update();
//    });
}

void MainScene::updatePosition()
{
    tpos_y += 1;
    //如果键盘控制了就可能导致下一步已经有了东西
    if(!moveable())
    {
        tpos_y -= 1;
    }
    if(touched())
    {
        qDebug()<<"touch";
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(!tsqare[i][j].isEmpty)
                {
                    mp[i + tpos_x][j + tpos_y].isEmpty = false;
                }
            }
        }

        clear(tpos_y, tpos_y + 4);

        creatShape(rand()%4);
        tpos_x = 8;
        tpos_y = 0;
        if(touched())
        {
            m_Timer.stop();

            GameOver *gameover = new GameOver();
            gameover->ms = this;
            gameover->show();

        }
        update();

    }

}



void MainScene::paintEvent(QPaintEvent *event)
{


    QPainter painter(this);
    painter.drawRect(0,0,500,750);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(!tsqare[i][j].isEmpty )
            {
                 painter.drawPixmap((tpos_x + i) * 25,(tpos_y + j) * 25 ,tsqare[i][j].sqare);
            }

        }
    }

    for(int i = 0; i < CNT_WIDTH; i++)
    {
        for(int j = 0; j < CNT_HEIGHT; j++)
        {
            if(!mp[i][j].isEmpty)
                painter.drawPixmap( i * 25,j * 25 ,mp[i][j].sqare);
        }
    }



}

void MainScene::keyPressEvent(QKeyEvent *event)
{
    this->setFocus(); //让主窗口获取焦点
    int ev = event->key();
    switch(ev)
    {
        case Qt::Key_Up:
        spinable(); //如果可以旋转将自动完成旋转
        update();
        break;
        case Qt::Key_Left:
        qDebug()<<"lefttouch";
        tpos_x -= 1;
        if(moveable())
        {
            update();

        }
        else
            tpos_x += 1;
        break;
        case Qt::Key_Right:
        tpos_x += 1;
        if(moveable())
        {
            update();

        }
        else
            tpos_x -= 1;
        break;
        case Qt::Key_Down:
        updatePosition();
        update();
        break;
    }
}



void MainScene::creatShape(int type)
{
    switch (type) {
        case 0:
        /*
         * 1
         *11
         * 1
         */
        clearShape();
        tsqare[3][0].isEmpty = false;
        tsqare[3][1].isEmpty = false;
        tsqare[3][2].isEmpty = false;
        tsqare[2][1].isEmpty = false;
        break;
        case 1:
        /*
         * 1111
         */
        clearShape();
        tsqare[0][1].isEmpty = false;
        tsqare[1][1].isEmpty = false;
        tsqare[2][1].isEmpty = false;
        tsqare[3][1].isEmpty = false;
        break;
        case 2:
        /* 111
         * 1
         */
        clearShape();
        tsqare[0][0].isEmpty = false;
        tsqare[0][1].isEmpty = false;
        tsqare[1][0].isEmpty = false;
        tsqare[2][0].isEmpty = false;
        break;
        case 3:
        /*
         * 11
         * 11
         */
        clearShape();
        tsqare[1][1].isEmpty = false;
        tsqare[1][2].isEmpty = false;
        tsqare[2][1].isEmpty = false;
        tsqare[2][2].isEmpty = false;
        break;

    }

}

void MainScene::clearShape()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            tsqare[i][j].isEmpty = true;
            //设置初始位置

        }
    }

}

bool MainScene::touched()
{
    for(int i = 0; i < 4; i ++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(!tsqare[i][j].isEmpty)
            {
                int x = tpos_x + i;
                int y = tpos_y + j + 1;
                if(!mp[x][y].isEmpty || y == 30)
                {
                    return true;
                }
            }
        }

    };
    return false;

}

bool MainScene::moveable()
{
    for(int i = 0; i < 4; i ++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(!tsqare[i][j].isEmpty)
            {
                if(tpos_x + i >= CNT_WIDTH || tpos_x + i < 0
                   || !mp[tpos_x + i][tpos_y + j].isEmpty)
                {
                    return false;
                }

            }
        }
    }
    return true;
}

bool MainScene::spinable()
{
    leftSpin();
    for(int i = 0; i < 4; i ++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(!tsqare[i][j].isEmpty)
            {
                if(tpos_x + i >= CNT_WIDTH || tpos_x + i < 0
                   || !mp[tpos_x + i][tpos_y + j].isEmpty)
                {
                    rightSpin();
                    return false;
                }

            }
        }
    }
    return true;
}

void MainScene::leftSpin()
{
    for(int j = 0; j < 2; j ++)
    {
        for(int i = j; i < 3 - j; i ++)
        {
            bool tmp = tsqare[j][i].isEmpty;
            tsqare[j][i].isEmpty = tsqare[i][3 - j].isEmpty;
            tsqare[i][3 - j].isEmpty = tsqare[3 - j][3 - i].isEmpty;
            tsqare[3 - j][3 - i].isEmpty = tsqare[3 - i][j].isEmpty;
            tsqare[3 - i][j].isEmpty = tmp;
        }
    }
}

void MainScene::rightSpin()
{
    for(int j = 0; j < 2; j ++)
    {
        for(int i = j; i < 3 - j; i ++)
        {

            Sqare tmp = tsqare[3 - i][j];
            tsqare[3 - i][j] = tsqare[3 - j][3 - i];
            tsqare[3 - j][3 - i] = tsqare[i][3 - j];
            tsqare[i][3 - j] = tsqare[j][i];
            tsqare[j][i] = tmp;
        }
    }
}

void MainScene::clear(int bgn,int ed)
{
    QVector<int> need_clear;
    for(int i = bgn; i <= ed && i < CNT_HEIGHT; i++)
    {

        bool flag = true;
        for(int j = 0; j < CNT_WIDTH; j++)
        {
            if(mp[j][i].isEmpty)
            {
                flag = false;
            }
        }
        if(flag) need_clear.push_back(i);
    }

    for(int &t : need_clear)
    {
        qDebug()<<t;
        for(int i = t; i > 0 ; i--)
        {
            for(int j = 0; j < CNT_WIDTH; j++)
            {
                mp[j][i].isEmpty = mp[j][i - 1].isEmpty;
            }
        }
        for(int j = 0; j < CNT_WIDTH; j++)
        {
            mp[j][0].isEmpty = true;
        }
    }
    score += need_clear.size();
    setScore(score);
    qDebug()<<score;
    if(!need_clear.empty() )
    {
        interval = ( (GAME_INTERVAL <= (score / 2) * 50 )?50:(GAME_INTERVAL - (score / 2) * 50) );
        qDebug()<<interval;
        m_Timer.setInterval(interval);
    }
    //interval = ( (interval == 50)?(interval - 50):50);
    //m_Timer.setInterval(interval);
}

void MainScene::clearBack()
{

    qDebug()<<"clear";
    tpos_x = 8;
    tpos_y = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            tsqare[i][j].isEmpty = true;
        }
    }
    for(int i = 0; i < CNT_WIDTH; i++)
    {
        for(int j = 0; j < CNT_HEIGHT; j++)
        {
            mp[i][j].isEmpty = true;
        }
    }
    update();
}

void MainScene::setButton()
{

    startButton = new QPushButton(this);
    stopButton = new QPushButton(this);
    continueButton = new QPushButton(this);
    record = new QLabel(this);


    setScore(0);
    startButton->setText(QStringLiteral("新游戏"));
    stopButton->setText(QStringLiteral("暂停"));
    continueButton->setText(QStringLiteral("继续"));

    record->setGeometry(QRect(520,100,200,50));
    startButton->setGeometry(QRect(520, 300,200,50));
    stopButton->setGeometry(QRect(520 , 350,200,50));
    continueButton->setGeometry(QRect(520,400,200,50));

    QFont ft;
    ft.setPointSize(24);
    record->setFont(ft);

    connect(startButton,SIGNAL(clicked(bool)),this, SLOT(startGame()));
    connect(stopButton,SIGNAL(clicked(bool)),this, SLOT(stopGame()));
    connect(continueButton,SIGNAL(clicked(bool)),this, SLOT(continueGame()));
}

void MainScene::setScore(int n)
{
    score = n;
    record->setText("SCORE: " +QString::number(score));
}

void MainScene::startGame()
{
    playGame();
    this->setFocus();
}

void MainScene::stopGame()
{
    //qDebug()<<"stop";
    m_Timer.stop();
    this->setFocus();
}

void MainScene::continueGame()
{
    m_Timer.start();
    this->setFocus();
}

