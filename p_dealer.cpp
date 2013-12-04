#include "p_dealer.h"
#include <stdio.h>
#include <cstdlib>
#include "p_player.h"
#include "p_card.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include "p_hand.h"
using namespace std;

dealer::dealer(){}
dealer::~dealer(void){}

card* dealer::makeDeck(card deck[]){
	int num[52];
	int suit[52];
	int number=1;
	int suits=1;
	for (int s=0; s<52; ++s) {//array of possible card suits
		if (suits<5) {
			suit[s]=suits;
			suits++;
		}
		else {
			suit[s]=1;
			suits=2;
		}
	}
	for (int n=0; n<52; ++n) {//array of possible card numbers
		if (number<14) {
			num[n]=number;
			number++;
		}
		else {
			num[n]=1;
			number=2;
		}
	}
	for (int x=0; x<52; ++x) {//builds deck
		deck[x].setValues(suit[x], num[x]);
	}
	return deck;//returns pointer to first card in the deck
}

void dealer::shuffle(card *d){//shuffles deck
	for (int i=0; i<10000; i++) {
                int j = 0;
                int k =0;
		j = rand() % 52;
		k = rand() % 52;
		card temp;
		temp = d[j];
		d[j] = d[k];
		d[k] = temp;
	}
	
}
	
card* dealer::deal5h(card* d,card hCards[]){//takes in pointer to deck[0] and empty card array, creates a 5 card array for human, and returns pointer to that hand
	hCards[0]=*d;
	hCards[1]=*(d+1);
	hCards[2]=*(d+2);
	hCards[3]=*(d+3);
	hCards[4]=*(d+4);
	return hCards;
}
	
card* dealer::deal5c(card* d,card cCards[]){//takes in pointer to deck[0] and empty card array, creates a 5 card array for human, and returns pointer to that hand
	cCards[0]=*(d+5);
	cCards[1]=*(d+6);
	cCards[2]=*(d+7);
	cCards[3]=*(d+8);
	cCards[4]=*(d+9);
	return cCards;
}	
	
	
void dealer::hSwap(card* d,card hCards[], int a, int b, int c, int e){//takes in pointer to a deck, array of cards, and 4 ints which represent desired cards to be swapped
if (a+b+c+e>9) { //handles 4 card swap, checks if player has an ace and if so swaps the other 4
	for (int x=0; x<5; x++) {
		if (hCards[x].getNumber()==1) {
			hCards[a-1]=*(d+10);
			hCards[b-1]=*(d+11);
			hCards[c-1]=*(d+12);
			hCards[e-1]=*(d+13);
		}
		else {//if player tried to beat the system and swap with no ace no swap happens
			
		}

	}
}
	else {//no ace all other swap combinations
		if (a==0 && b!=0 && c!=0 && e!=0) {
			hCards[b-1]=*(d+10);
			hCards[c-1]=*(d+11);
			hCards[e-1]=*(d+12);
		}
		if (b==0 && a!=0 && c!=0 && e!=0) {
			hCards[a-1]=*(d+10);
			hCards[c-1]=*(d+11);
			hCards[e-1]=*(d+12);
		}
		if (a!=0 && b!=0 && c==0 && e!=0) {
			hCards[a-1]=*(d+10);
			hCards[b-1]=*(d+11);
			hCards[e-1]=*(d+12);
		}
		if (a!=0 && b!=0 && c!=0 && e==0) {
			hCards[a-1]=*(d+10);
			hCards[b-1]=*(d+11);
			hCards[c-1]=*(d+10);
		}
		if (a==0 && b==0 && c!=0 && e!=0) {
			hCards[c-1]=*(d+10);
			hCards[e-1]=*(d+11);
		}
		if (a==0 && b!=0 && c==0 && e!=0) {
			hCards[b-1]=*(d+10);
			hCards[e-1]=*(d+11);
		}
		if (a==0 && b!=0 && c!=0 && e==0) {
			hCards[b-1]=*(d+10);
			hCards[c-1]=*(d+11);
		}
		if (a!=0 && b==0 && c==0 && e!=0) {
			hCards[a-1]=*(d+10);
			hCards[e-1]=*(d+11);
		}
		if (a!=0 && b==0 && c!=0 && e==0) {
			hCards[a-1]=*(d+10);
			hCards[c-1]=*(d+11);
		}
		if (a!=0 && b!=0 && c==0 && e==0) {
			hCards[a-1]=*(d+10);
			hCards[b-1]=*(d+11);
		}
		if (a==0 && b==0 && c==0 && e!=0) {
			hCards[e-1]=*(d+10);
		}
		if (a!=0 && b==0 && c==0 && e==0) {
			hCards[a-1]=*(d+10);
		}
		if (a==0 && b!=0 && c==0 && e==0) {
			hCards[b-1]=*(d+10);
		}
		if (a==0 && b==0 && c!=0 && e==0) {
			hCards[c-1]=*(d+10);
		}
		if (b==0 && a==0 && e==0 && c==0) {
			
		}
	}

}
	
void dealer::cSwap(card* d,card cCards[], int a, int b, int c, int e){//takes in pointer to a deck, array of cards, and 4 ints which reprensent desired cards to be swapped
	if (a+b+c+e>9) { //handles 4 card swap, checks if player has an ace and if so swaps the other 4
		for (int x=0; x<5; x++) {
			if (cCards[x].getNumber()==1) {
				cCards[a-1]=*(d+14);
				cCards[b-1]=*(d+15);
				cCards[c-1]=*(d+16);
				cCards[e-1]=*(d+17);
			}
			else {//if player tried to beat the system and swap with no ace no swap happens
				
			}
			
		}
	}
	else {//no ace all other swap combinations
		if (a==0 && b!=0 && c!=0 && e!=0) {
			cCards[b-1]=*(d+14);
			cCards[c-1]=*(d+15);
			cCards[e-1]=*(d+16);
		}
		if (b==0 && a!=0 && c!=0 && e!=0) {
			cCards[a-1]=*(d+14);
			cCards[c-1]=*(d+15);
			cCards[e-1]=*(d+16);
		}
		if (a!=0 && b!=0 && c==0 && e!=0) {
			cCards[a-1]=*(d+14);
			cCards[b-1]=*(d+15);
			cCards[e-1]=*(d+16);
		}
		if (a!=0 && b!=0 && c!=0 && e==0) {
			cCards[a-1]=*(d+14);
			cCards[b-1]=*(d+15);
			cCards[c-1]=*(d+16);
		}
		if (a==0 && b==0 && c!=0 && e!=0) {
			cCards[c-1]=*(d+14);
			cCards[e-1]=*(d+15);
		}
		if (a==0 && b!=0 && c==0 && e!=0) {
			cCards[b-1]=*(d+14);
			cCards[e-1]=*(d+15);
		}
		if (a==0 && b!=0 && c!=0 && e==0) {
			cCards[b-1]=*(d+14);
			cCards[c-1]=*(d+15);
		}
		if (a!=0 && b==0 && c==0 && e!=0) {
			cCards[a-1]=*(d+14);
			cCards[e-1]=*(d+15);
		}
		if (a!=0 && b==0 && c!=0 && e==0) {
			cCards[a-1]=*(d+14);
			cCards[c-1]=*(d+15);
		}
		if (a!=0 && b!=0 && c==0 && e==0) {
			cCards[a-1]=*(d+14);
			cCards[b-1]=*(d+15);
		}
		if (a==0 && b==0 && c==0 && e!=0) {
			cCards[e-1]=*(d+14);
		}
		if (a!=0 && b==0 && c==0 && e==0) {
			cCards[a-1]=*(d+14);
		}
		if (a==0 && b!=0 && c==0 && e==0) {
			cCards[b-1]=*(d+14);
		}
		if (a==0 && b==0 && c!=0 && e==0) {
			cCards[c-1]=*(d+14);
		}
		if (b==0 && a==0 && e==0 && c==0) {
			
		}
	}
	
}

int dealer::tieBreaker(card* hptr, card* cptr, hand hh, hand ch){
	int x;
	int hhigh = hh.getHighest(hptr);
	int chigh = ch.getHighest(cptr);
	if (hhigh > chigh) {
		x=hhigh;
	}
	if (hhigh < chigh) {
		x=chigh;
	}
	if (hhigh == chigh) {
		x=20;
	}
	return x;
}
	
void dealer::dealerDriver(void){
dealer dlr;//make a dealer, necessary to call dealer functions

        //make deck
        card* d;
        card deck[52];
        d = dlr.makeDeck(deck);

        //print deck
        cout <<"deck: "<<endl;
        for (int i=0; i<52; ++i) {
        cout << (d+i)->getSuit() << (d+i)->getNumber() <<  endl;
        }

        //shuffle
        dlr.shuffle(d);
        //print shuffled deck
        cout << "now shuffled" << endl;
        for (int i=0; i<52; ++i) {
                cout << (d+i)->getSuit() << (d+i)->getNumber() <<  endl;
        }

        //deal human cards
        card hCards[5];
        card* hptr;
        hptr = dlr.deal5h(d, hCards);
        //print human cards
        cout << "humans hand" << endl;
        for (int j=0; j<5; j++) {
                cout << (hptr+j)->getSuit() << (hptr+j)->getNumber() << endl;
        }

        //deal cp cards
        card cCards[5];
        card* cptr;
        cptr = dlr.deal5c(d, cCards);
        //print cp cards
        cout << "computer's hand" << endl;
        for (int k=0; k<5; k++) {
                cout << (cptr+k)->getSuit() << (cptr+k)->getNumber() << endl;
        }

        //swap Human cards
        dlr.hSwap(d, hCards, 0, 0, 2, 0);//numbers represent which cards the player wants to swap 1 being hCards[0], function needs 4 numbers, 0 can be used as a place filler
        //print new hand
        cout << "humans new hand" << endl;
        for (int j=0; j<5; j++) {
                cout << (hptr+j)->getSuit() << (hptr+j)->getNumber() << endl;
        }

        //swap cp cards
        dlr.cSwap(d, cCards, 1, 5, 2, 0);//numbers represent which cards the player wants to swap 1 being hCards[0], function needs 4 numbers, 0 can be used as a place filler
	 cout << "computer's new hand" << endl;  for (int j=0; j<5; j++) {
                cout << (cptr+j)->getSuit() << (cptr+j)->getNumber() << endl;
        }
        hand *h = new hand();
        cout<<"human hand scored: "<< h->scoreHand(hCards)<<endl;
        cout<<"computer hand scored: "<< h->scoreHand(cCards)<<endl;
}
	
	
	
	
	
	
	
	

