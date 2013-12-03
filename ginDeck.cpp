#include <iostream>
#include <string>
#include "ginDeck.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

ginDeck::ginDeck(){
	stockArray[52];
	for(int i = 0; i < 32; i++){
		ginCard card(0,0,NULLSUIT,false);
		communityArray[i] = card;}

}

void ginDeck::generateginDeck(){
	deckPointer = &stockArray[0];
	int suit = 0;
	int cardsPerSuit;
	int cardCount = 0;
	while(suit<4){
		switch(suit){
			case 0:
				for(cardsPerSuit=1;cardsPerSuit<14;cardsPerSuit++){
					ginCard card(cardsPerSuit, cardsPerSuit, HEARTS, true);
					if (card.value > 10 ) {
						card.value = 10;
					}
					stockArray[cardCount] = card;
					cardCount++;
				}
				suit++;
				break;
			case 1:
				for(cardsPerSuit=1;cardsPerSuit<14;cardsPerSuit++){
					ginCard card(cardsPerSuit, cardsPerSuit, SPADES, true);
					if (card.value > 10 ) {
						card.value = 10;
					}
					stockArray[cardCount] = card;
					cardCount++;
				}
				suit++;
				break;
			case 2:
				for(cardsPerSuit=1;cardsPerSuit<14;cardsPerSuit++){
					ginCard card(cardsPerSuit, cardsPerSuit, DIAMONDS, true);
					if (card.value > 10 ) {
						card.value = 10;
					}
					stockArray[cardCount] = card;
					cardCount++;
				}
				suit++;
				break;
			case 3:
				for(cardsPerSuit=1;cardsPerSuit<14;cardsPerSuit++){
					ginCard card(cardsPerSuit, cardsPerSuit, CLUBS, true);
					if (card.value > 10 ) {
						card.value = 10;
					}
					stockArray[cardCount] = card;
					cardCount++;
				}
				suit++;
				break;
		} //terminate switch statement
	} //terminate while loop
} //terminate generateginDeck

void ginDeck::shuffleginCards(int q){
	srand(time(NULL));
	for (int i = 0; i<1000; i++) { 				//first for loop
		int j = rand() % q;
		int k = rand() % q;
		ginCard temp(0,0,NULLSUIT, false);
		temp = stockArray[j];
		stockArray[j] = stockArray[k];
		stockArray[k] = temp;
	}											//end first for loop
	for(int l=0; l<52;l++){						//begin second for loop
		stockArray[l] = stockArray[l];
	}											//end second for loop

	// for(int cardDebug=0; cardDebug<52; cardDebug++) {
		// cout << stockArray[cardDebug].card << " of " << stockArray[cardDebug].suit << endl;
	// }

}												//terminate shuffleginCards

void ginDeck::checkForEmptyStockPile() {
	if(stockArray[0].suit == NULLSUIT) {
		for(int i = 1; i<31; i++)
		{
			stockArray[i-1] = communityArray[i];
			ginCard card(0,0,NULLSUIT,false);
			communityArray[i] = card;
		}
		shuffleginCards(31);
	}
}

void ginDeck::discard(ginCard cardToDiscard){
	for(int i = 31; i > 0 ; i--){
		communityArray[i] = communityArray[i-1];
}
	communityArray[0] = cardToDiscard;
}

ginCard ginDeck::drawCommunityginCard(){
	ginCard temp = communityArray[0];
	for(int i = 1; i < 32 ; i++){
		communityArray[i-1] = communityArray[i];
	}
	return temp;
}

ginCard ginDeck::drawStockginCard(){
	ginCard temp = stockArray[0];
	for(int i = 1; i < 52 ; i++){
		stockArray[i-1] = stockArray[i];
	}
	return temp;
}

void ginDeck::showCommunityginCard(){
	string suit;
	switch(communityArray[0].suit) {
		case 1: suit = "Hearts";
				break;
		case 2: suit = "Spades";
				break;
		case 3: suit = "Diamonds";
				break;
		case 4: suit = "Clubs";
				break;
	}
	cout << "-------------------------------------------------------------------" << endl;
	cout << "Community ginCard" << endl;
	cout << communityArray[0].card << ", " << suit << endl;
	cout << "-------------------------------------------------------------------" << endl;
	}

void ginDeck::showStockginCard(){
	string suit;
	switch(stockArray[0].suit) {
		case 1: suit = "Hearts";
				break;
		case 2: suit = "Spades";
				break;
		case 3: suit = "Diamonds";
				break;
		case 4: suit = "Clubs";
				break;
	}
	cout << "-------------------------------------------------------------------" << endl;
	cout << "Stock ginCard" << endl;
	cout << stockArray[0].card << ", " << suit << endl;
	cout << "-------------------------------------------------------------------" << endl;
	}
