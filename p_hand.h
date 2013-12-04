#ifndef PHAND_H
#define PHAND_H
#include "p_card.h"

class hand{
    public:
        hand(void);
        ~hand(void);
        int scoreHand(card *c);//needs to be written
        int winner(card *c1, card *c2);//needs to be written, will be composed of tie(), getHighest() and scoreHand() to determine winner
        int tie(int p1, int p2);//needs to be written
        int getLowest(card *c); //returns lowest card
        int getHighest(card *c);    //returns highest card, ace = 15 for comparison reasons
        bool hasCard(card *c, int s, int n);//tests if a 5 card hand as a particular card with suit s, number n
        bool hasNumCard(card *c, int n);//tests if a 5 card hand has a particular card for when suit doesn't matter
        bool hasRoyalFlush(card *c, int s);
        bool hasStraightFlush(card *c, int s, int l);
        bool has4ofaKind(card *c, int n);
        bool hasFullHouse(card *c);
        bool hasFlush(card *c, int s);
        bool hasStraight(card *c, int l);
        bool has3ofaKind(card *c, int n);
        bool has2Pair(card *c);
        bool hasPair(card *c, int n);
	/***********************Hand driver*****************/
        void handDriver();




};
#endif
