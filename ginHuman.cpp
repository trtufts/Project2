#include "ginHuman.h"
#include <iostream>
#include <string>
#include <sstream>

//using namespace std;


ginHuman::~ginHuman() {

}

 void ginHuman::enterName(ginHuman &player, display &interface, ginDeck &d){
	stringstream messageString;
	string nameString;
	char key;

	messageString.str("");
	messageString << "Please enter your name with [a-z] and hit [enter] when you're done" << endl;
	interface.bannerIndex = 0;
	interface.bannerBottom(messageString.str());

	key;

	while(key != '\n') {

		key = player.getKey(interface, d);

		while(isalpha(key) || key == ' ') {
			nameString += key;

			messageString.str("");
			messageString << nameString << endl;
			interface.bannerBet(messageString.str());

			key = player.getKey(interface, d);
		}
	}

	interface.bannerBetClear("");

	player.name = nameString;
}

bool ginHuman::draw(char drawSelect, ginDeck &d){
	switch(drawSelect){
		case 'c': cards[10] = d.drawCommunityginCard();
				  return true;
		case 's': cards[10] = d.drawStockginCard();
				  return true;
		default:  return false;
	}
}

bool ginHuman::toss(char tossSelect, ginDeck &d, display &interface){
	char tossKey;
	int tossIndex;
	bool doneSelecting;
	bool knockOutcome;

	stringstream messageString;

	refreshDisplay(interface, d);

	switch(tossSelect){
		case 'd' :	messageString.str("");
					messageString << "Press [0-9] to discard card [0-9] or any other key to discard card 10" << endl;
					interface.bannerIndex = 5;
					interface.bannerBottom(messageString.str());

					tossKey = runDisplay(interface, d);

					if(0 <= (tossKey - '0') && (tossKey - '0') <= 9) {
						tossIndex = tossKey - '0';
						containerDiscard(tossIndex, d);
					} else {
						containerDiscard(10, d);
					}
					return true;

		case 'k' :	messageString.str("");
					messageString << "Press [0-9] to discard card [0-9] or any other key to discard card 10" << endl;
					interface.bannerBottom(messageString.str());
					interface.bannerIndex = 5;


					tossKey = runDisplay(interface, d);

					if(0 <= (tossKey - '0') && (tossKey - '0') <= 9) {
						tossIndex = tossKey - '0';
						containerDiscard(tossIndex, d);
					} else {
						containerDiscard(10, d);
					}

					doneSelecting = false;

					while(doneSelecting == false){
						messageString.str("");
						messageString << "Press [y] to specify a meld or [n] to stop specifying melds" << endl;
						interface.bannerIndex = 6;
						interface.bannerBottom(messageString.str());
						switch(runDisplay(interface, d)){
							case 'y' :	meldSelector(interface, d);
										break;
							case 'n' :	doneSelecting = true;
										break;
							default  :	doneSelecting = false;
						}
					}

					knockOutcome = knock();
					if(knockOutcome == true) {
						messageString.str("");
						messageString << "You've successfully knocked!"  << endl;
						interface.bannerIndex = 7;
						interface.bannerBottom(messageString.str());
						sleep(2);
						return true;
					} else {
						messageString.str("");
						messageString << "You can't knock because your deadwood count is greater than 10." << endl;
						interface.bannerIndex = 8;
						interface.bannerBottom(messageString.str());
						refreshDisplay(interface, d);
						for(int i=0; i<10; i++) {
							cards[i].deadwood = true;
						}
						sleep(2);
						return true;
					}
		default :	return false;
	}
}

void ginHuman::refreshDisplay(display &interface, ginDeck &d){
	int cardX = 30;
	int cardYginComputer = 5;
	int cardYginHuman = 35;

	stringstream messageString;

	//Print legend
	messageString.str("");
	messageString << "-----------Legend-----------" << endl;
	interface.displayText(messageString.str(), 0, 12);

	messageString.str("");
	messageString << "c      : draw community card" << endl;
	interface.displayText(messageString.str(), 0, 13);

	messageString.str("");
	messageString << "s      : draw stock card    " << endl;
	interface.displayText(messageString.str(), 0, 14);

	messageString.str("");
	messageString << "d      : discard            " << endl;
	interface.displayText(messageString.str(), 0, 15);

	messageString.str("");
	messageString << "k      : knock              " << endl;
	interface.displayText(messageString.str(), 0, 16);

	messageString.str("");
	messageString << "0-9    : select card [0-9]  " << endl;
	interface.displayText(messageString.str(), 0, 17);

	messageString.str("");
	messageString << "<Space>: select last card   " << endl;
	interface.displayText(messageString.str(), 0, 18);

	messageString.str("");
	messageString << "   Your turn" << endl;
	interface.displayText(messageString.str(), 56, 25);

	messageString.str("");
	messageString << "0      1      2      3      4      5      6      7      8      9     <Space>" << endl;
	interface.displayText(messageString.str(), cardX+2, cardYginHuman+5);

	interface.captureInput();
	for(int i=0; i<11; i++) {
		if(cards[i].suit == NULLSUIT) {
				interface.drawBoxInvis(cardX+i*7, cardYginHuman, 6, 5, A_INVIS);
		} else {
			interface.displayginCard(cardX+i*7, cardYginHuman, cards[i].suit, cards[i].card, A_NORMAL); // show human cards
		}
		if(i != 10) {
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

void ginHuman::meldSelector(display &interface, ginDeck &d){
	vector<ginCard> meld;
	int card;
	int numberOfginCards;
	int cardLocations[numberOfginCards];
	stringstream messageString;

	messageString.str("");
	messageString << "Press [3] or [4] to specify a meld of [3] or [4] cards" << endl;
	interface.bannerIndex = 9;
	interface.bannerBottom(messageString.str());

	numberOfginCards = runDisplay(interface, d) - '0';
	while(numberOfginCards < 3 || numberOfginCards > 4) {
		numberOfginCards = runDisplay(interface, d) - '0';
	}

	messageString.str("");
	messageString << "Press [0-9] to add card [0-9] to your meld" << endl;
	interface.bannerIndex = 10;
	interface.bannerBottom(messageString.str());
	for(int i = 0; i < numberOfginCards; i++){

		card = runDisplay(interface, d) - '0';
		while(card < 0 || card > 9) {
			card = runDisplay(interface, d) - '0';
		}
		cardLocations[i] = card;
		meld.push_back(cards[card]);
	}

	if(isMeld(meld) == true) {
		messageString.str("");
		messageString << "Yep, it's a meld!" << endl;
		interface.bannerBottom(messageString.str());
		for(int i=0; i<numberOfginCards; i++) {
			cards[cardLocations[i]].deadwood = false;
			meld.pop_back();
		}
	} else {
		messageString.str("");
		messageString << "Nope, not a meld." << endl;
		interface.bannerBottom(messageString.str());
	}
	refreshDisplay(interface, d);
	sleep(2);
}

//Currently displaying player cards and community card. Loops for keyPressed flag
char ginHuman::runDisplay(display &interface, ginDeck &d){
	char key;
	int cardX = 30;
	int cardYginComputer = 5;
	int cardYginHuman = 35;
	bool keyPressed = false;
	stringstream messageString;

	//Print legend
	messageString.str("");
	messageString << "-----------Legend-----------" << endl;
	interface.displayText(messageString.str(), 0, 12);

	messageString.str("");
	messageString << "c      : draw community card" << endl;
	interface.displayText(messageString.str(), 0, 13);

	messageString.str("");
	messageString << "s      : draw stock card    " << endl;
	interface.displayText(messageString.str(), 0, 14);

	messageString.str("");
	messageString << "d      : discard            " << endl;
	interface.displayText(messageString.str(), 0, 15);

	messageString.str("");
	messageString << "k      : knock              " << endl;
	interface.displayText(messageString.str(), 0, 16);

	messageString.str("");
	messageString << "0-9    : select card [0-9]  " << endl;
	interface.displayText(messageString.str(), 0, 17);

	messageString.str("");
	messageString << "<Space>: select last card   " << endl;
	interface.displayText(messageString.str(), 0, 18);

	messageString.str("");
	messageString << "   Your turn" << endl;
	interface.displayText(messageString.str(), 56, 25);

	messageString.str("");
	messageString << "0      1      2      3      4      5      6      7      8      9     <Space>" << endl;
	interface.displayText(messageString.str(), cardX+2, cardYginHuman+5);

	while(keyPressed == false){
		key = interface.captureInput();

		for(int i=0; i<11; i++) {

			if(cards[i].suit == NULLSUIT) {
				interface.drawBoxInvis(cardX+i*7, cardYginHuman, 6, 5, A_INVIS);
			} else {
				interface.displayginCard(cardX+i*7, cardYginHuman, cards[i].suit, cards[i].card, A_NORMAL); // show human cards
			}
			if(i != 10) {
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

		if( key > 0 ){
			keyPressed = true;
		}
	}
	return key;
}

char ginHuman::getKey(display &interface, ginDeck &d) {
	char key;
	int cardX = 30;
	int cardYginComputer = 5;
	int cardYginHuman = 35;
	bool keyPressed = false;
	stringstream messageString;

	//Print legend
	messageString.str("");
	messageString << "-----------Legend-----------" << endl;
	interface.displayText(messageString.str(), 0, 12);

	messageString.str("");
	messageString << "c      : draw community card" << endl;
	interface.displayText(messageString.str(), 0, 13);

	messageString.str("");
	messageString << "s      : draw stock card    " << endl;
	interface.displayText(messageString.str(), 0, 14);

	messageString.str("");
	messageString << "d      : discard            " << endl;
	interface.displayText(messageString.str(), 0, 15);

	messageString.str("");
	messageString << "k      : knock              " << endl;
	interface.displayText(messageString.str(), 0, 16);

	messageString.str("");
	messageString << "0-9    : select card [0-9]  " << endl;
	interface.displayText(messageString.str(), 0, 17);

	messageString.str("");
	messageString << "<Space>: select last card   " << endl;
	interface.displayText(messageString.str(), 0, 18);

	messageString.str("");
	messageString << "   Your turn" << endl;
	interface.displayText(messageString.str(), 56, 25);

	messageString.str("");
	messageString << "0      1      2      3      4      5      6      7      8      9     <Space>" << endl;
	interface.displayText(messageString.str(), cardX+2, cardYginHuman+5);


	while(keyPressed == false){
		key = interface.captureInput();

		for(int i=0; i<10; i++) {

			interface.displayginCard(cardX+i*7, cardYginHuman, -1, -1, A_NORMAL); // show human cards
			interface.displayginCard(cardX+i*7, cardYginComputer, -1, -1, A_NORMAL); // show computer cards
		}

		interface.displayginCard(65, 20, -1, -1, A_NORMAL);

		if( key > 0 ){
			keyPressed = true;
		}
	}
	return key;
}
