#include "sqare.h"
#include "config.h"

Sqare::Sqare()
{
   isEmpty = true;
   sqare.load(GAME_SQARE);
   sqare = sqare.scaled(25, 25);

   setPosition(0,0);
}

void Sqare::setPosition(int x, int y)
{

    positon_x = x;
    positon_y = y;
}
