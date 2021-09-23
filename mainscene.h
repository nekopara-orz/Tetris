#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include "sqare.h"
#include "config.h"
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //初始化场景
    void initScene();
    void playGame();
    void updatePosition();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void creatShape(int type);
    void clearShape();
    bool touched(); //判断是否有接触
    bool moveable();
    bool spinable();
    void leftSpin();
    void rightSpin();
    void clear(int bgn,int ed); //清除已经填满的行
    void clearBack(); //清空所有内容
    void setButton();
    void setScore(int n);
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *continueButton;
    QLabel *record;

    Sqare mp[CNT_WIDTH][CNT_HEIGHT];
    Sqare tsqare[4][4];
    int tpos_x,tpos_y;
    int score; //当前积分
    int interval;
    QTimer m_Timer;

private slots:
    void startGame();
    void stopGame();
    void continueGame();



};
#endif // MAINSCENE_H
