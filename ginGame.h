#ifndef GIN_H
#define GIN_H


#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>

#include <iostream>
#include <string>
#include <fstream>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "ginDeck.h"
#include "ginCard.h"
#include "ginPlayer.h"
#include "ginHuman.h"
#include "ginComputer.h"
#include "ginScoring.h"
#include "display.h"

using namespace std;

void stub_PrintResize(void);
enum suits { NULLSUIT, SPADES, HEARTS, CLUBS, DIAMONDS };

static void ginDetectResize (int sig);
void stub_PrintResize(void);
void dealginCards(ginPlayer &human, ginPlayer &computer, ginDeck &d);
extern display gameDisplay;

stringstream messageString;
ginHuman player1;
ginComputer player2("Computer");
ginDeck pile;
string adArray[20];
int currentAd;

extern double playerBalance;



int gin(){

    	// Settings for card colors (these can be set outside of the display class)
	init_pair(1, COLOR_BLACK, COLOR_WHITE); // for card outline
	init_pair(2, COLOR_BLACK, COLOR_WHITE); // for spades and clubs
	init_pair(3, COLOR_RED, COLOR_WHITE);  // for hearts and diamonds
	init_pair(4, COLOR_BLUE, COLOR_WHITE); // for turned over card
	init_pair(5, COLOR_GREEN, COLOR_BLACK); // for box drawing
	init_pair(6, COLOR_BLUE, COLOR_BLACK); // for banner display
	init_pair(7, COLOR_BLACK, COLOR_WHITE); // for text display
	init_pair(8, COLOR_WHITE, COLOR_BLACK); // for banner clear display
	init_pair(9, COLOR_BLACK, COLOR_BLACK); // for invisible cards




    int cols = gameDisplay.getCols();
	int lines = gameDisplay.getLines();
	gameDisplay.eraseBox(0,0,cols,lines);



	gameDisplay.bannerArray[0] = "Please enter your name with [a-z] and hit [enter] when you're done"; //
	gameDisplay.bannerArray[1] = "Please enter your bet with [0-9] and hit [enter] when you're done"; //
	gameDisplay.bannerArray[2] = "Press [c] for community card, [s] for stock card, or [q] to quit"; //
	gameDisplay.bannerArray[3] = "Press [d] to discard or [k] to knock"; //
	gameDisplay.bannerArray[4] = "New round!";
	gameDisplay.bannerArray[5] = "Press [0-9] to discard card [0-9] or any other key to discard card 10"; //
	gameDisplay.bannerArray[6] = "Press [y] to specify a meld or [n] to stop specifying melds"; //
	gameDisplay.bannerArray[7] = "You've successfully knocked!"; //
	gameDisplay.bannerArray[8] = "You can't knock because your deadwood count is greater than 10."; //
	gameDisplay.bannerArray[9] = "Press [3] or [4] to specify a meld of [3] or [4] cards";
	gameDisplay.bannerArray[10] = "Press [0-9] to add card [0-9] to your meld";

	int arrayIndex = 0;
	string advertisement;
	ifstream adFile;
	adFile.open("advertisement.txt");
	while(!adFile.eof()){
		getline(adFile, advertisement);
		adArray[arrayIndex] = advertisement;
		arrayIndex++;
	}
	adFile.close();

	signal(SIGWINCH, ginDetectResize); // enable the window resize signal
	bool ongoing = true;

	char quitKey;
	char drawKey;
	time_t startTime;
	time_t stopTime;
	int timeSpent;
	int numTurns = 0;
	extern int cardCount;

	//Print scores
	messageString.str("");
	messageString << "      Your score: " << player1.score << endl;
	gameDisplay.displayText(messageString.str(), 0, 30);
	messageString.str("");
	messageString << "ginComputer's score: " << player2.score << endl;
	gameDisplay.displayText(messageString.str(), 0, 31);
	messageString.str("");
	messageString << "         Balance: $" << playerBalance << endl;
	gameDisplay.displayText(messageString.str(), 0, 33);

	player1.enterName(player1, gameDisplay, pile);
	//gameDisplay.backgroundWhite();

	bool legalBet = false;
	while(legalBet == false){
	ginScoring::placeBet(player1, gameDisplay, pile);
	if (ginScoring::getBet() < playerBalance + 1){
		playerBalance = playerBalance - ginScoring::getBet();
		legalBet = true;}
	else
		gameDisplay.clearDisplay();
	}

	//Print scores
	messageString.str("");
	messageString << "      Your score: " << player1.score << endl;
	gameDisplay.displayText(messageString.str(), 0, 30);
	messageString.str("");
	messageString << "ginComputer's score: " << player2.score << endl;
	gameDisplay.displayText(messageString.str(), 0, 31);
	messageString.str("");
	messageString << "         Balance: $" << playerBalance << endl;
	gameDisplay.displayText(messageString.str(), 0, 33);

	time(&startTime);

	while(player1.score < 100 && player2.score < 100) {
		pile.generateginDeck();
		pile.shuffleginCards(52);

		memset(pile.communityArray, 0, 32);

		dealginCards(player1, player2, pile);
		ongoing = true;
		player1.knockers = false;
		player2.knockers = false;

		while (ongoing == true){

			srand(time(NULL));
			messageString.str("");
			currentAd = rand()%20;
			messageString << adArray[currentAd] << endl;
			gameDisplay.bannerTop(messageString.str());

			pile.checkForEmptyStockPile();
			messageString.str("");
			messageString << "Press [c] for community card, [s] for stock card, or [q] to quit" << endl;
			gameDisplay.bannerIndex = 2;
			gameDisplay.bannerBottom(messageString.str());

			drawKey = player1.runDisplay(gameDisplay, pile);
			while(player1.draw(drawKey, pile) == false) {
				if(drawKey == 'q') {
					break;
				}
				drawKey = player1.runDisplay(gameDisplay, pile);
			}

			if(drawKey == 'q') {
				break;
			}

			messageString.str("");
			messageString << "Press [d] to discard or [k] to knock" << endl;
			gameDisplay.bannerIndex = 3;
			gameDisplay.bannerBottom(messageString.str());

			char tossKey = player1.runDisplay(gameDisplay, pile);
			while(player1.toss(tossKey, pile, gameDisplay) == false) {
				tossKey = player1.runDisplay(gameDisplay, pile);
			}
			pile.checkForEmptyStockPile();
			player1.refreshDisplay(gameDisplay, pile);
			if (player1.knockers == true){
				ongoing = false;
			}
			else if(ongoing == true){
				player2.turn(gameDisplay, pile);
			}
			numTurns++;

			// srand(time(NULL));
			// messageString.str("");
			// messageString << adArray[rand()%20] << endl;
			// gameDisplay.bannerTop(messageString.str());
		}

		if(drawKey == 'q') {
			break;
		}

		player2.showginComputerginCards(gameDisplay, pile);
		ginScoring::calcScore(player1, player2);

		//Print scores
		messageString.str("");
		messageString << "      Your score: " << player1.score << endl;
		gameDisplay.displayText(messageString.str(), 0, 30);
		messageString.str("");
		messageString << "ginComputer's score: " << player2.score << endl;
		gameDisplay.displayText(messageString.str(), 0, 31);
		messageString.str("");
		messageString << "         Balance: $" << playerBalance << endl;
		gameDisplay.displayText(messageString.str(), 0, 33);

		messageString.str("");
		messageString << "New round!" << endl;
		gameDisplay.bannerIndex = 4;
		gameDisplay.bannerBottom(messageString.str());
		player1.refreshDisplay(gameDisplay, pile);
		sleep(8);
	}

	if(drawKey == 'q') {
		time(&stopTime);
		timeSpent = ( stopTime - startTime );
		cardCount = 10 + numTurns;

		messageString.str("");
		messageString << "ginCards played: " << cardCount << endl;
		gameDisplay.bannerBottom(messageString.str());


			for(;;) {
				quitKey = gameDisplay.captureInput();

				if(quitKey > 0) {
					time(&stopTime);
					break;
				}
			}

		return 666;
	}

	ginScoring::calcPoints(player1, player2);
	ginScoring::calcPayout(player1, player2, gameDisplay);
	player2.showginComputerginCards(gameDisplay, pile);
	if( ginScoring::getWinner() == 1)
		playerBalance = playerBalance + 2*(ginScoring::getBet());
	cardCount = 10 + numTurns;

	messageString.str("");
	messageString << "         Balance: $" << playerBalance << endl;
	gameDisplay.displayText(messageString.str(), 0, 33);

	for(;;) {
		quitKey = gameDisplay.captureInput();

		if(quitKey > 0) {
			time(&stopTime);
			break;
		}
	}

	timeSpent = ( stopTime - startTime );
}

void dealginCards(ginPlayer &human, ginPlayer &computer, ginDeck &d){
	int cardsToDeal = 0;
	int i = 0;
	while(cardsToDeal < 20){
		human.cards[i] = d.stockArray[cardsToDeal];
		cardsToDeal++;
		computer.cards[i] = d.stockArray[cardsToDeal];
		cardsToDeal++;
	i++;
}
	d.communityArray[0] = d.stockArray[20];
	for(int j = 21; j < 52; j++){
		d.stockArray[j-21] = d.stockArray[j];
}
	for(int j = 31; j < 52; j++){
		ginCard card(0,0,NULLSUIT,false);
		d.stockArray[j] = card;}
}

/*
 * This is a simple stub that should be replaced with what the game does
 * when the screen resizes.
 */
//void stub_PrintResize(void) {
	    // gets the new screen size
	//int cols = gameDisplay.getCols();
	//int lines = gameDisplay.getLines();
	   // // setups a message stream
	// stringstream messageString;
	// messageString << "Terminal is " << cols << "x" << lines;
	// // prints out the information of the new screen size in a top banner
	// gameDisplay.bannerTop(messageString.str());
//}

/*
 * This is the interrupt service routine called when the resize screen
 * signal is captured.
 */
void ginDetectResize(int sig) {
	// update the display class information with the new window size
    gameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
    signal(SIGWINCH, ginDetectResize);
        /*INSERT YOUR OWN SCREEN UPDATE CODE instead of stub_PrintResize*/
	//stub_PrintResize();

	gameDisplay.clearDisplay();

	gameDisplay.bannerBottom(gameDisplay.bannerArray[gameDisplay.bannerIndex]);

	//Print scores
	//if(gameDisplay.getLines() > 31) {
		messageString.str("");
		messageString << "     Current pot: $" << 2*ginScoring::getBet() << endl;
		gameDisplay.displayText(messageString.str(), 0, 28);
		messageString.str("");
		messageString.str("");
		messageString << "      Your score: " << player1.score << endl;
		gameDisplay.displayText(messageString.str(), 0, 30);
		messageString.str("");
		messageString << "ginComputer's score: " << player2.score << endl;
		gameDisplay.displayText(messageString.str(), 0, 31);
		messageString.str("");
		messageString << "         Balance: $" << playerBalance << endl;
		gameDisplay.displayText(messageString.str(), 0, 33);
		messageString.str("");
		messageString << adArray[currentAd] << endl;
		gameDisplay.bannerTop(messageString.str());
	//}

	player1.refreshDisplay(gameDisplay, pile);
}


#endif
