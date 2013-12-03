#include "ginPlayer.h"
#include <iostream>
#include <sstream>
using namespace std;

ginCard cards[11];

//constructor
ginPlayer::ginPlayer(string playerName){
	score = 0;
	name = playerName;
	for(int i = 0; i < 11; i++){
		ginCard card(0,0,NULLSUIT,false);
		cards[i] = card;
		knockers = false;
	}
}

//default constructor
ginPlayer::ginPlayer(){
	score = 0;
	name;
	for(int i = 0; i < 11; i++){
		ginCard card(0,0,NULLSUIT,false);
		cards[i] = card;
		knockers = false;
	}
}

//deconstructor
ginPlayer::~ginPlayer(){
}

bool ginPlayer::knock(){
	stringstream messageString;

	int deadwoodCount = calcDeadwood();

	if(deadwoodCount <= 10) {
		knockers = true;
		return true;
	} else {
		return false;
	}
}

bool ginPlayer::isMeld( vector<ginCard> potentialMeld ) {
	//check for a set
	bool isMeld = true;
	int firstginCardValue = potentialMeld.at(0).card;
	for(int i=1; i<potentialMeld.size(); i++) {
		if(potentialMeld.at(i).card != firstginCardValue || potentialMeld.at(i).deadwood == false) {
			isMeld = false;
			break;
		}
	}

	//check for a run
	if(isMeld == false) {
		isMeld = true;
		int max = 0;
		int min = 14;
		int firstginCardSuit = potentialMeld.front().suit;
		int cardValue;
		for(int i=0; i<potentialMeld.size(); i++) {
			if(potentialMeld.at(i).suit != firstginCardSuit || potentialMeld.at(i).deadwood == false) {
				isMeld = false;
				break;
			}

			cardValue = potentialMeld.at(i).card;
			if(cardValue < min) {
				min = cardValue;
			}
			if(cardValue > max) {
				max = cardValue;
			}
		}

		if( (max - min) != (potentialMeld.size() - 1) ) {
			isMeld = false;
		}
	}

	return isMeld;
}

int ginPlayer::calcDeadwood(){
	int pointsCount = 0;
	for(int i = 0; i < 10; i++){
		if(cards[i].deadwood == true){
			pointsCount += cards[i].value;
		}
	}
	return pointsCount;
}

void ginPlayer::containerDiscard(int cardLocation, ginDeck &d) {
	d.discard(cards[cardLocation]) ;

	for(int i = cardLocation; i<10; i++){
		cards[i] = cards[i+1];
	}
	ginCard nullginCard(0,0,NULLSUIT,false);
	cards[10] = nullginCard;
}
