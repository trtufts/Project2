#ifndef PPLAYER_H
#define PPLAYER_H
#include "display.h"
//extern display gameDisplay;

class player{
public:
    player(double m);
    ~player(void);
    double getMoney();
    void setMoney(double b);
    double makeMove(int hmoney,display gameDisplay, int y, int x);
protected:
    double money;

};
#endif

