#ifndef GFMAIN_H
#define GFMAIN_H

#include "display.h"
#include "Deck.h"
#include "Player.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

extern int cardCount;
extern double playerBalance;
extern display gameDisplay;
Deck gameDeck;
display cardAsk;
display playerAsk;
Player comp1; //computer player
Player comp2; //computer player
Player comp3; //computer player
Player human; //human player - player 0
int cardsinDeck[52];

void goFish() {
string temp;
ifstream fin("advertisement.txt");
while(getline(fin,temp)) {}
fin.close();

	stringstream messageString;
	for(int b = 0; b<52; b++)
	  cardsinDeck[b] = b+1;
	srand(time(0));
	gameDeck.ShuffleCards(cardsinDeck);
	for(int j =0; j<28; j+=4){			//Deal cards
		comp1.addCard(cardsinDeck[j]);
		comp2.addCard(cardsinDeck[j+1]);
		comp3.addCard(cardsinDeck[j+2]);
		human.addCard(cardsinDeck[j+3]);
		cardCount++;
		cardsinDeck[j] = -1;
		cardsinDeck[j+1] = -1;
		cardsinDeck[j+2] = -1;
		cardsinDeck[j+3] = -1;
	}
	int deckCards = 0;
	int comp1Cards = 0;
	int comp2Cards = 0;
	int comp3Cards = 0;
	int k;
	for(k=0; k<52; k++){
		if(cardsinDeck[k] != -1)
			deckCards++;
		if(comp1.cardsInHand[k] != -1)
			comp1Cards++;
		if(comp2.cardsInHand[k] != -1)
			comp2Cards++;
		if(comp3.cardsInHand[k] != -1)
			comp3Cards++; 		
	}

	int playerToAsk  = 0;
	int cardToAskFor = 0;
	int cardsToGet   = 0;
	string nothing   = "";
clear();
	gameDisplay.displayHumCards(human.cardsInHand);
	gameDisplay.updateScreen(deckCards, comp1Cards, comp2Cards, comp3Cards, comp1.scorePile, comp2.scorePile, comp3.scorePile, human.scorePile);


//	mvprintw(30,10,temp.c_str());


	bool gameTime = true;
	while (gameTime == true) {
	  HumanPlayerTurn:
	    playerToAsk  = 0;
	    cardToAskFor = 0;
	    cardsToGet   = 0;
	    mvprintw(37,0, "Who do you want to ask? [1,2,3] (9 to Quit) \n");
	    gameDisplay.displayHumCards(human.cardsInHand);
	    gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
	    cin >> playerToAsk;
	    if (playerToAsk == 9)
		break;
	    clear();
	    mvprintw(37,0, "Ask player %d for which card? [1-13]\n", playerToAsk);
	    gameDisplay.displayHumCards(human.cardsInHand);
	    gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
	    cin >> cardToAskFor;
	    clear();
	    char hold;
	    switch (playerToAsk) {
	    	case 1:
			cardsToGet = comp1.getCard(cardToAskFor);
			if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
				human.addCard(gameDeck.drawCard(cardsinDeck));
				cardCount++;
				deckCards--;
				mvprintw(37,0, "Go Fish! [Press any character to continue] \n");
				gameDisplay.displayHumCards(human.cardsInHand);
				gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
				cin >> hold;
				clear();
			}
			else {
				human.addCard(cardsToGet);
				cardCount++;
				playerBalance+=5;
				mvprintw(37,0, "You Guessed Right! [Press any character to continue] \n");
				gameDisplay.displayHumCards(human.cardsInHand);
				gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
				cin >> hold;
				cin.clear();
				clear();
			}
			break;
		case 2:
			cardsToGet = comp2.getCard(cardToAskFor);
			if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
				human.addCard(gameDeck.drawCard(cardsinDeck));
				cardCount++;
				deckCards--;
				mvprintw(37,0, "Go Fish! [Press any character to continue] \n");
				gameDisplay.displayHumCards(human.cardsInHand);
				gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
				cin >> hold;
				cin.clear();
				clear();
			}
			else{
				human.addCard(cardsToGet);
				cardCount++;
				playerBalance+=5;
				mvprintw(37,0, "You Guessed Right! [Press any character to continue] \n");
				gameDisplay.displayHumCards(human.cardsInHand);
				gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
				cin >> hold;
				cin.clear();
				clear();
			}
			break;
		case 3:
			cardsToGet = comp3.getCard(cardToAskFor);
			if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
				human.addCard(gameDeck.drawCard(cardsinDeck));
				cardCount++;
				deckCards--;
				mvprintw(37,0, "Go Fish! [Press any character to continue] \n");
				gameDisplay.displayHumCards(human.cardsInHand);
				gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
				cin >> hold;
				cin.clear();
				clear();
			}
			else{
				human.addCard(cardsToGet);
				cardCount++;
				playerBalance+=5;
				mvprintw(37,0, "You Guessed Right! [Press any character to continue]");
				gameDisplay.displayHumCards(human.cardsInHand);
				gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
				cin >> hold;
				cin.clear();
				clear();
			}
				break;
			default:
				cout << ":( \n" ;
		}
		gameDisplay.displayHumCards(human.cardsInHand);
		gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
		clear();
		if (cardsToGet != 0)
		  goto HumanPlayerTurn;
		else
		  goto Comp1Turn;
//-------------------------------------------------------------------------------------------------------------------------
	Comp1Turn:
		playerToAsk  = 0;
		cardToAskFor = 0;
		cardsToGet   = 0;
		srand(time(0));
		playerToAsk = rand() % 4; 
		while (playerToAsk == 1)
			playerToAsk = rand() % 4; 
		cardToAskFor = comp1.cardsInHand[rand() % 52];
		while (cardToAskFor == -1)
			cardToAskFor = comp1.cardsInHand[rand() % 52];
		cardToAskFor = cardToAskFor%13;                                  //Face value of card asked for
      		if(cardToAskFor == 0)                                            //If player asked for king
        		cardToAskFor = 13; 
		mvprintw(37,0, "Comp1 asks player %d for card %d", playerToAsk, cardToAskFor);
		gameDisplay.displayHumCards(human.cardsInHand);
		gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile, human.scorePile);
		clear();
		sleep(1);
		switch (playerToAsk) {
		case 0:
			cardsToGet = human.getCard(cardToAskFor);
			if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
				comp1.addCard(gameDeck.drawCard(cardsinDeck));
				comp1Cards++;
				deckCards--;
			}
			else{
				comp1.addCard(cardsToGet);
				comp1Cards++;
			}
			break;
		case 2:	
			cardsToGet = comp2.getCard(cardToAskFor);
			if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
				comp1.addCard(gameDeck.drawCard(cardsinDeck));
				comp1Cards++;
				deckCards--;
			}
			else {
				comp1.addCard(cardsToGet);
				comp1Cards++;
				comp2Cards--;
			}
			break;
		case 3:
			cardsToGet = comp3.getCard(cardToAskFor);
			if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
				comp1.addCard(gameDeck.drawCard(cardsinDeck));
				comp1Cards++;
				deckCards--;
			}
			else {
				comp1.addCard(cardsToGet);
				comp1Cards++;
				comp3Cards--;
			}
			break;
		default:
			cout << ":( \n" ;
		}
		gameDisplay.displayHumCards(human.cardsInHand);
		gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
		clear();
		if (cardsToGet != 0)
			goto Comp1Turn;
		else
			goto Comp2Turn;
//----------------------------------------------------------------------------------------------
	Comp2Turn:
		playerToAsk = 0;
		cardToAskFor = 0;
		cardsToGet = 0;
		srand(time(0));
		playerToAsk = rand() % 4; 
		while (playerToAsk == 2)
			playerToAsk = rand() % 4; 
		cardToAskFor = comp2.cardsInHand[rand() % 52];
		while (cardToAskFor == -1)
			cardToAskFor = comp2.cardsInHand[rand() % 52];
		cardToAskFor = cardToAskFor%13;                                  //Face value of card asked for
      		if(cardToAskFor == 0)                                            //If player asked for king
        		cardToAskFor = 13; 
		mvprintw(37,0, "Comp2 asks player %d for card %d", playerToAsk, cardToAskFor);
		gameDisplay.displayHumCards(human.cardsInHand);
		gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
		clear();
		sleep(1);
		switch (playerToAsk) {
			case 0:
				cardsToGet = human.getCard(cardToAskFor);
				if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
					comp2.addCard(gameDeck.drawCard(cardsinDeck));
					comp2Cards++;
					deckCards--;
				}
				else{
					comp2.addCard(cardsToGet);
					comp2Cards++;
				}
				break;
			case 1:
				cardsToGet = comp1.getCard(cardToAskFor);
				if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
					comp2.addCard(gameDeck.drawCard(cardsinDeck));
					comp2Cards++;
					deckCards--;
				}
				else {
					comp2.addCard(cardsToGet);
					comp2Cards++;
					comp1Cards--;
				}
				break;
			case 3:
				cardsToGet = comp3.getCard(cardToAskFor);
				if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
					comp2.addCard(gameDeck.drawCard(cardsinDeck));
					comp2Cards++;
					deckCards--;
				}
				else {
					comp2.addCard(cardsToGet);
					comp2Cards++;
					comp3Cards--;
				}
				break;
			default:
				cout << ":( \n" ;
		}//end switch	
		gameDisplay.displayHumCards(human.cardsInHand);
		gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
		clear();
		if (cardsToGet != 0)
			goto Comp2Turn;
		else
			goto Comp3Turn;
//-----------------------------------------------------------------------------------------------
	Comp3Turn:
		playerToAsk  = 0;
		cardToAskFor = 0;
		cardsToGet   = 0;
		srand(time(0));
		playerToAsk = rand() % 4; 
		while (playerToAsk == 3)
			playerToAsk = rand() % 4; 
		cardToAskFor = comp3.cardsInHand[rand() % 52];
		while (cardToAskFor == -1)
			cardToAskFor = comp3.cardsInHand[rand() % 52];
		cardToAskFor = cardToAskFor%13;                                  //Face value of card asked for
      		if(cardToAskFor == 0)
        		cardToAskFor = 13; 
		mvprintw(37,0, "Comp3 asks player %d for card %d", playerToAsk, cardToAskFor);
		gameDisplay.displayHumCards(human.cardsInHand);
		gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
		clear();
		sleep(1);
		switch (playerToAsk) {
			case 0:
				cardsToGet = human.getCard(cardToAskFor);
				if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
					comp3.addCard(gameDeck.drawCard(cardsinDeck));
					comp3Cards++;
					deckCards--;
				}
				else{
					comp3.addCard(cardsToGet);
					comp3Cards++;
				}
				break;
			case 1:
				cardsToGet = comp1.getCard(cardToAskFor);
				if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
					comp3.addCard(gameDeck.drawCard(cardsinDeck));
					comp3Cards++;
					deckCards--;
				}
				else {
					comp3.addCard(cardsToGet);
					comp3Cards++;
					comp1Cards--;
				}
				break;
			case 2:
				cardsToGet = comp2.getCard(cardToAskFor);
				if((cardsToGet == 0)&&(gameDeck.drawCard(cardsinDeck)!= -1)) {
					comp3.addCard(gameDeck.drawCard(cardsinDeck));
					comp3Cards++;
					deckCards--;
				}
				else {
					comp3.addCard(cardsToGet);
					comp3Cards++;
					comp2Cards--;
				}
				break;
			default:
				cout << ":( \n" ;
		}//end switch	
		gameDisplay.displayHumCards(human.cardsInHand);
		gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
		clear();
		if (cardsToGet != 0)
			goto Comp3Turn;
		else
			goto HumanPlayerTurn; 

	}
	int hSc=0;
	int C1 = 0;
	int C2 = 0;
	int C3 = 0;
	for(int i=0; i<13; i++) {
		hSc += human.scorePile[i];
		C1 += comp1.scorePile[i];
		C1 += comp1.scorePile[i];
		C2 += comp2.scorePile[i];
		C3 += comp3.scorePile[i];
	}

        clear();
	if((hSc>C1)&&(hSc>C2)&&(hSc>C3)) {
        	mvprintw(37,0, "Final Score: %d, YOU WIN!", hSc);
		playerBalance += 100;
	}
	else{
		mvprintw(37,0, "Final Score: %d, YOU LOSE :(", hSc);
		playerBalance += -100;
	}
        gameDisplay.displayHumCards(human.cardsInHand);
        gameDisplay.updateScreen(deckCards,comp1Cards,comp2Cards,comp3Cards,comp1.scorePile,comp2.scorePile,comp3.scorePile,human.scorePile);
        clear();
	sleep(4);
}
		
#endif	
