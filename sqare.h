#ifndef SQARE_H
#define SQARE_H

#include <QPixmap>



class Sqare
{

public:
    Sqare();
    int positon_x;
    int positon_y;
    bool isEmpty;
    QPixmap sqare;
    void draw(int type);
    void setPosition(int x,int y);

};

#endif // SQARE_H
