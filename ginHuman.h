#ifndef GHUMAN_H
#define GHUMAN_H

#include "ginDeck.h"
#include "ginPlayer.h"
#include "display.h"
#include <ctype.h>
#include <string>
#include <vector>
#include <sstream>

class ginHuman : public ginPlayer {
public:
	ginHuman(string playerName) : ginPlayer(playerName){};
	ginHuman() : ginPlayer(){};
	~ginHuman();

	void enterName(ginHuman &player, display &interface, ginDeck &d);
	bool draw(char drawSelect, ginDeck &d);
	bool toss(char tossSelect, ginDeck &d, display &interface);
	void refreshDisplay(display &interface, ginDeck &d);
	void meldSelector(display &interface, ginDeck &d);
	char runDisplay(display &interface, ginDeck &d);
	char getKey(display &interface, ginDeck &d);

	enum suits { NULLSUIT, SPADES, HEARTS, CLUBS, DIAMONDS };
};

#endif
