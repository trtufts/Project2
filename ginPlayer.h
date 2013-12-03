#ifndef PLAYER_H
#define PLAYER_H
#include "ginCard.h"
#include "ginDeck.h"
#include <string>
#include <vector>
#include <algorithm>

class ginPlayer{

public:
	 ginPlayer(string name);
	 ginPlayer();
	~ginPlayer();

	bool knock();
	int calcDeadwood();
	//void meldSelector();
	bool isMeld( vector<ginCard> potentialMeld );
	void containerDiscard(int cardLocation, ginDeck &d);

	ginCard cards[11];
	int score;
	string name;
	bool knockers;
	enum suits { NULLSUIT, SPADES, HEARTS, CLUBS, DIAMONDS };
};

#endif
