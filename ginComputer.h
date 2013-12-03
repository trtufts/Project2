#ifndef COMPUTER_H
#define COMPUTER_H

#include "ginDeck.h"
#include "ginPlayer.h"
#include "display.h"
#include <string>
#include <vector>
#include <time.h>

class ginComputer : public ginPlayer {
public:
	ginComputer(string playerName) : ginPlayer(playerName){};
	~ginComputer();
	bool knock(int deadwood);
	void turn(display &interface, ginDeck &d);
	void refreshDisplay(display &interface, ginDeck &d);
	void showginComputerginCards(display &interface, ginDeck &d);

	//void layoff();
	//bool isMeld( vector<ginCard>* potentialMeld );

private:
	// void chooseginCardToDraw();
	// void chooseginCardToDiscard();
	// void chooseToKnockOrDiscard();
	// void chooseToTakeFirstginCard();
};

#endif

