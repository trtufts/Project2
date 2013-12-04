#ifndef PDEALER_H
#define PDEALER_H
#include "p_player.h"
#include "p_card.h"
#include "p_pot.h"
#include "p_hand.h"
class dealer{	
public:
	dealer();
	~dealer(void);
    card* makeDeck(card d[]);
    void shuffle(card* d);
    card* deal5h(card* d, card hCards[]);
	card* deal5c(card* d, card hCards[]);
    void hSwap(card* d,card hCards[], int a, int b, int c, int e);
	void cSwap(card* d,card hCards[], int a, int b, int c, int e);
    int Score(card hCards[]);
    int tieBreaker(card* hptr, card* cptr, hand hh, hand ch);
    void dealerDriver();	
private:
};

#endif
