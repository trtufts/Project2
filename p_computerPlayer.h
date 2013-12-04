#ifndef PCOMPUTERPLAYER_H
#define PCOMPUTERPLAYER_H
#include "Player.h"

class ComputerPlayer
{
public:
	//constructor&destructor
	ComputerPlayer();
        ~ComputerPlayer();
   
   //takes in hand&human player bet, spits out AI bet amount
	double determineBet(Hand* currentHand, double humanBet);
	
	//takes in hand, spits out list of cards to swap
	Hand* determineSwap(Hand* currentHand);
}


#endif /* COMPUTERPLAYER_H */