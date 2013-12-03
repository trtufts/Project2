#include "ginComputer.h"
#include <string>
#include <sstream>

//using namespace std;


ginComputer::~ginComputer() {

}

void ginComputer::turn(display &interface, ginDeck &d){
	srand(time(NULL));
	int i = rand()%2;
	int j = rand()%10;
	refreshDisplay(interface, d);
	sleep(2);
	switch(i){
		case 0: 	cards[10] = d.drawCommunityginCard() ;
					break;

		case 1: 	cards[10] = d.drawStockginCard() ;
					break;
	}
	refreshDisplay(interface, d);
	containerDiscard(j, d);
	refreshDisplay(interface, d);
	sleep(2);
}

bool ginComputer::knock(int deadwood) {

	if(deadwood < 10) {
		cout << "Legal knock" << endl;
		return true;
	}
	else {
		cout << "Illegal knock" << endl;
		return false;
	}
}

void ginComputer::refreshDisplay(display &interface, ginDeck &d){
	int cardX = 30;
	int cardYginComputer = 5;
	int cardYginHuman = 35;

	stringstream messageString;

	messageString.str("");
	messageString << "ginComputer's turn" << endl;
	interface.displayText(messageString.str(), 56, 25);

	messageString.str("");
	interface.bannerBottom(messageString.str());

	interface.captureInput();
	for(int i=0; i<11; i++) {
		if(cards[i].suit == NULLSUIT) {
				interface.drawBoxInvis(cardX+i*7, cardYginComputer, 6, 5, A_INVIS);
		} else {
			interface.displayginCard(cardX+i*7, cardYginComputer, -1, -1, A_NORMAL); // show computer cards
		}
	}
	switch(d.communityArray[0].suit) {
		case NULLSUIT:	interface.drawBoxInvis(55, 20, 6, 5, A_INVIS);
						break;
		default: 		interface.displayginCard(55, 20, d.communityArray[0].suit, d.communityArray[0].card, A_NORMAL);
						break;
	}

	switch(d.stockArray[0].suit) {
		case NULLSUIT:	interface.drawBoxInvis(65, 20, 6, 5, A_INVIS);
						break;
		default: 		interface.displayginCard(65, 20, -1, -1, A_NORMAL);
						break;
	}
}

void ginComputer::showginComputerginCards(display &interface, ginDeck &d){
	int cardX = 30;
	int cardYginComputer = 5;

	interface.captureInput();
	for(int i=0; i<10; i++) {
		interface.displayginCard(cardX+i*7, cardYginComputer, cards[i].suit, cards[i].card, A_NORMAL); // show computer cards
	}
	switch(d.communityArray[0].suit) {
		case NULLSUIT:	interface.drawBoxInvis(55, 20, 6, 5, A_INVIS);
						break;
		default: 		interface.displayginCard(55, 20, d.communityArray[0].suit, d.communityArray[0].card, A_NORMAL);
						break;
	}

	switch(d.stockArray[0].suit) {
		case NULLSUIT:	interface.drawBoxInvis(65, 20, 6, 5, A_INVIS);
						break;
		default: 		interface.displayginCard(65, 20, -1, -1, A_NORMAL);
						break;
	}
}
