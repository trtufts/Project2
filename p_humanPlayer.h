#ifndef PHUMANPLAYER_H
#define PHUMANPLAYER_H
#include "p_player.h"
#include "p_card.h"
#include "p_dealer.h"
class humanPlayer: public player
{
public:
    humanPlayer(double m);
    ~humanPlayer(void);
    int replaceCards(display gameDisplay, int line, int x);
    int* chooseCards(int n,display gameDisplay, int y, int x);//functions with replaceCards();
    /***********driver********/
    void humanPlayerDriver();
};

#endif
