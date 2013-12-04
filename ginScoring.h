#ifndef GSCORING_H
#define GSCORING_H

#include "ginPlayer.h"
#include "display.h"
#include "ginDeck.h"
#include "ginHuman.h"
#include <sstream>
#include <string>

class ginScoring{

public:
	static void calcScore(ginPlayer &human, ginPlayer &computer);
	static void calcPoints(ginPlayer &human, ginPlayer &computer);
	static void calcPayout(ginPlayer &human, ginPlayer &computer, display &interface);
	static void placeBet(ginHuman &player, display &interface, ginDeck &d);
	static double getBet();
	static int getWinner();
};


#endif


