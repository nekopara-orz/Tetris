#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "mainscene.h"

#include <QWidget>

namespace Ui {
class GameOver;
}

class GameOver : public QWidget
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = nullptr);
    ~GameOver();
    MainScene *ms;


private:
    Ui::GameOver *ui;
private slots:
    void closePage();

};

#endif // GAMEOVER_H
