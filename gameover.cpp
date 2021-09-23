#include "gameover.h"
#include "ui_gameover.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
GameOver::GameOver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    QPushButton *button;
    button = new QPushButton(this);
    //button->setGeometry(QRect(50,50,100,25));
    button->setText(QStringLiteral("确定"));
    QLabel *text = new QLabel();
    text->setText(QStringLiteral("游戏结束"));

    QFont ft;
    ft.setPointSize(24);
    text->setFont(ft);
    //设置颜色使用QPalette
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::red);
    text->setPalette(pa);



    QHBoxLayout *qlt = new QHBoxLayout();
    qlt->addStretch();
    qlt->addWidget(text);
    qlt->addStretch();



    QHBoxLayout *qlb = new QHBoxLayout();
    qlb->addStretch();
    qlb->addWidget(button);
    qlb->addStretch();


    QVBoxLayout *qlv = new QVBoxLayout;
    qlv->addStretch();
    qlv->addLayout(qlt);
    qlv->addStretch();
    qlv->addLayout(qlb);
    qlv->addStretch();
    this->setLayout(qlv);

    connect(button,SIGNAL(clicked(bool)),this,SLOT(closePage()));
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::closePage()
{
    ms->clearBack();
    this->hide();
}


