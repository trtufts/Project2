/* Title: Project 1 ECE373 Example driver artifact for Display class
 * Author: John Gontowicz, Sefan, Amrit, Michaela
 * Project: Five Hand Poker
 */

#ifndef POKER_H
#define POKER_H

#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "p_card.h"
#include "p_dealer.h"
#include "p_hand.h"
#include <iomanip>
#include "p_humanPlayer.h"
#include <unistd.h>
#include <fstream>

using namespace std;

// Signal Subroutine for Window Resize
static void pokerdetectResize (int sig); 
// stub artifact for what the game does when the screen resizes
void stub_PrintResize(void); 

// The gameDisplay object is global, because the static signal handler object
// needs to access the dynamic object.
extern display gameDisplay;
extern int cardCount;
extern double playerBalance;


#define OUTLINE COLOR_BLUE
#define INSIDE COLOR_WHITE
#define DIVIDER COLOR_GREEN
#define BANNER COLOR_WHITE

int poker()
{
	

	// using a stringstream rather than a string to make making the banner easier
	stringstream messageString;
	
	// various variable declarations
	srand(time(0));
	int cardX = 0;
	int cardY = 0;
	int suit=0;
	int number=0;
	
	//int dragX = 0;
	//int dragY = 0;
	//char key1; //the first key entered
	//char key2; //the second key entered
	//char key3; //the third key entered
	//char key4; //the fourth key entered
	//int inputs = 0; //checks to see the number of inputs given - need 4
	//bool first = true;
	//bool check = false;
	double hum = 0;
	double comp = 0;
	//char moveOn;
	// enable a interrupt triggered on a window resize
	signal(SIGWINCH, pokerdetectResize); // enable the window resize signal
	
	/* You can uncomment and change the colors for various cards here*/
	init_pair(1, OUTLINE, COLOR_BLACK); // for card outline
	init_pair(2, COLOR_BLACK, INSIDE); // for spades and clubs
	init_pair(3, COLOR_RED, INSIDE);  // for hearts and diamonds
	init_pair(4, COLOR_BLUE, INSIDE); // for turned over card 
	init_pair(5, COLOR_RED, INSIDE); // for box drawing
	init_pair(6, BANNER, COLOR_BLACK); // for banner display
	init_pair(7, DIVIDER, COLOR_BLACK); //for the divider banners
	
	gameDisplay.dividerBanner();
	
	dealer dlr;//make a dealer, necessary to call dealer functions
	humanPlayer hplr(playerBalance);//make a human player with incoming player balance
	player cplr(100);//make a cp player with 100 dollars
	hand hh; //make human hand
	hand ch; //make cp hand
	card* d;
	card deck[52];
	d = dlr.makeDeck(deck);
	pot thePot(0);
	
	int lines = gameDisplay.getLines();
	int cols = gameDisplay.getCols();
	gameDisplay.eraseBox(0,0,cols,lines);
	int y = double(lines)*.15+3;
 	int x = double(cols)-double(cols)*.3+5;
	
	/********************ads********/
	string line;
	ifstream file;
	string ad;
	int count=0;
	string temp[1000];
	file.open("advertisement.txt");//path to ad text file
	if (!file) {
		ad = "cannot open file";
	}
	if (file.is_open())
	{
		while (getline(file,line))
		{
			temp[count]=line;
			count++;
		}
		int randLine = rand() % count;
		ad = temp[randLine];
		file.close();
	}
	/********************************/
	
	for(;;){
        for(;;){
			y = double(lines)*.15+3;
			thePot.resetPot();
			gameDisplay.clearText();
			//make deck
			//make a pot with 0 dollars
			hum = hplr.getMoney();
			comp = cplr.getMoney();
			gameDisplay.moneyBanners(hum, comp);
			gameDisplay.potBanner(0);
			gameDisplay.adBanner(ad);
			
			//shuffle
			dlr.shuffle(d);
			dlr.shuffle(d);
			gameDisplay.outputText("The Deck has been Shuffled. Here is your hand!",y,x);
			y = y+1;
			
			//create human cards
			card hCards[5];
			cardCount=cardCount+5;
			card* hptr;
			hptr = dlr.deal5h(d, hCards); //hptr now points the array hCards which contains the humans hand 
			
			//create cp cards
			card cCards[5];
			card* cptr;
			cptr = dlr.deal5c(d, cCards);
			
			cardX = 15;
			cardY = 10;
			for (int j=0; j<5; j++) 
			{
                gameDisplay.outputText("             ",8,cardX);
                gameDisplay.outputText("             ",9,cardX);
                int temp = cardY;
                suit = (hptr+j)->getSuit();
                number = (hptr+j)->getNumber();
                gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                cardY = 35;
                suit = 0;
                number = (cptr+j)->getNumber();
                gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                cardX = cardX + 20;
                cardY = temp;
			}
			
			
			gameDisplay.outputText("Now it's time for the first round of betting!",y+1,x);
			
			y = y+2;
			
			double hbet = hplr.makeMove(hplr.getMoney(),gameDisplay, y,x);
			y = y+3;
			
			if (hbet >= 0)
			{
				thePot.inputToPot(hbet);
				hplr.setMoney(-hbet);
				thePot.inputToPot(hbet);
				cplr.setMoney(-hbet);
				string string = "You bet:  $";
				string = string + static_cast<ostringstream*>( &(ostringstream() << hbet) )->str();
				gameDisplay.outputText(string,y+1,x);
			}
			else{
				gameDisplay.outputText("You Folded... The computer gets the pot.",y+1,x);  
				cplr.setMoney(thePot.getPot());
				break;
			}
			y = y+2; 
			gameDisplay.potBanner(thePot.getPot());
			gameDisplay.moneyBanners(hplr.getMoney(), cplr.getMoney());
			
			card hhCards[5];
			card ccCards[5];
			for(int i = 0; i < 5;i++){
				hhCards[i]=hCards[i];
				ccCards[i]=cCards[i];
			}
			int n = 0;
			n = hplr.replaceCards(gameDisplay,y,x);
			cardCount=cardCount+n;
			if(n>0)   y = y+7;
			int* swap = hplr.chooseCards(n,gameDisplay,y,x);
			y = y+4;
			dlr.hSwap(d,hCards,swap[0],swap[1],swap[2],swap[3]);
			for (int a=0; a<4; a++) {
				swap[a]=0;
			}
			
			
			//shows the new swapped cards
			cardX = 15;
			cardY = 10;
			for (int j=0; j<5; j++) 
			{
                int temp = cardY;
                suit = (hptr+j)->getSuit();
                number = (hptr+j)->getNumber();
                if((hhCards[j].getSuit()==hCards[j].getSuit())&&(hhCards[j].getNumber()==hCards[j].getNumber()))
					gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                else{
                    cardY = 8;
                    gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                    gameDisplay.outputText("      ^      ",cardY+11,cardX);
                    gameDisplay.outputText("   Swapped   ",cardY+12,cardX);
                }
                if((ccCards[j].getSuit()==cCards[j].getSuit())&&(ccCards[j].getNumber()==cCards[j].getNumber())){
                    cardY = 35;
                }
                else{
                    cardY = 33;
                }
                //suit = (cptr+j)->getSuit();
                suit = 0;
                number = (cptr+j)->getNumber();
                gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                cardX = cardX + 20;
                cardY = temp;
				
			}
			stringstream st;
			string sts2 = "";
			string sts = "Number of Cards swapped: ";
			st << n;
			st >> sts2;
			sts = sts + sts2;
			
			
			gameDisplay.outputText(sts,y+1,x);
			y= y+1;
			
			//Second round of betting
			hbet = hplr.makeMove(hplr.getMoney(),gameDisplay, y+1,x);
			y = y+4;
			if (hbet >= 0)
			{
				thePot.inputToPot(hbet);
				hplr.setMoney(-hbet);
				thePot.inputToPot(hbet);
				cplr.setMoney(-hbet);
				string string = "You bet:  $";
				string = string + static_cast<ostringstream*>( &(ostringstream() << hbet) )->str();
				gameDisplay.outputText(string,y+1,x);
			}
			else{
				gameDisplay.outputText("You Folded... The computer gets the pot.",y+1,x);  
				cplr.setMoney(thePot.getPot());
				break;
			}
			
			y = y+1; 
			gameDisplay.potBanner(thePot.getPot());
			gameDisplay.moneyBanners(hplr.getMoney(), cplr.getMoney());
			
			int hScore = hh.scoreHand(hptr);
			int cScore = ch.scoreHand(cptr);
			string humScore;
			string compScore;
			
			switch(hScore){
				case 1:{
					humScore = "Human Score:\t\tHigh Card Only";
				}
					break;
                case 2:{
					humScore = "Human Score:\t\t1 Pair";
				}
					break;
                case 3:{
					humScore = "Human Score:\t\t2 Par";
				}
					break;
                case 4:{
					humScore = "Human Score:\t\t3 of a Kind";
				}
					break;
                case 5:{
					humScore = "Human Score:\t\tStraight";
				}
					break;
                case 6:{
					humScore = "Human Score:\t\tFlush";
				}
					break;
                case 7:{
					humScore = "Human Score:\t\tFull House";
				}
					break;
                case 8:{
					humScore = "Human Score:\t\t4 of a Kind";
				}
					break;
                case 9:{
					humScore = "Human Score:\t\tStraight Flush";
				}
					break;
                case 10:{
					humScore = "Human Score:\t\tRoyal Flush";
				}
				default:
					break;
			}
			switch(cScore){
				case 1:{
					compScore = "Computer Score:\tHigh Card Only";
				}
					break;
                case 2:{
					compScore = "Computer Score:\t1 Pair";
				}
					break;
                case 3:{
					compScore = "Computer Score:\t2 Par";
				}
					break;
                case 4:{
					compScore = "Computer Score:\t3 of a Kind";
				}
					break;
                case 5:{
					compScore = "Computer Score:\tStraight";
				}
					break;
                case 6:{
					compScore = "Computer Score:\tFlush";
				}
					break;
                case 7:{
					compScore = "Computer Score:\tFull House";
				}
					break;
                case 8:{
					compScore = "Computer Score:\t4 of a Kind";
				}
					break;
                case 9:{
					compScore = "Computer Score:\tStraight Flush";
				}
					break;
                case 10:{
					compScore = "Computer Score:\tRoyal Flush";
				}
				default:
					break;
			}
			
			y=y+1;
			
			gameDisplay.outputText(humScore, y+1,x);
			gameDisplay.outputText(compScore,y+2,x);
			y = y+4;
			
			if (hScore == cScore) {//handles tie
				int highest = dlr.tieBreaker(hptr, cptr, hh, ch);
				int hhigh = hh.getHighest(hptr);
				int chigh = ch.getHighest(cptr);
				if (hhigh == highest) {
					hScore=hScore+1;
				}
				if (chigh == highest) {
					cScore=cScore+1;
				}
				if (chigh == hhigh) {
					cplr.setMoney((thePot.getPot()/2));
					hplr.setMoney((thePot.getPot()/2));
					gameDisplay.outputText("It's a tie. You split the pot!", y,x);
				}
			}
			
			if (hScore > cScore) {
				hplr.setMoney(thePot.getPot());
                gameDisplay.outputText("YOU WON!!", y,x);
			}
			
			if (hScore < cScore) {
				cplr.setMoney(thePot.getPot());
                gameDisplay.outputText("You lost...", y,x);
			}
			
			y = y+2;
			cardX = 15;
			cardY = 10;
			for (int j=0; j<5; j++) 
			{
                int temp = cardY;
                suit = (hptr+j)->getSuit();
                number = (hptr+j)->getNumber();
                if((hhCards[j].getSuit()==hCards[j].getSuit())&&(hhCards[j].getNumber()==hCards[j].getNumber()))
					gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                else{
                    cardY = 8;
                    gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                    gameDisplay.outputText("             ",cardY+11,cardX);
                    gameDisplay.outputText("             ",cardY+12,cardX);
                }
                if((ccCards[j].getSuit()==cCards[j].getSuit())&&(ccCards[j].getNumber()==cCards[j].getNumber())){
                    cardY = 35;
                }
                else{
                    cardY = 33;
                }
                suit = (cptr+j)->getSuit();
                number = (cptr+j)->getNumber();
                gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
                cardX = cardX + 20;
                cardY = temp;
				
			}
			
			gameDisplay.potBanner(0);
			gameDisplay.moneyBanners(hplr.getMoney(), cplr.getMoney());
			if(hplr.getMoney()<=0)
			{
				gameDisplay.outputText("You are Bankrupt!! Better luck next time!",y+2,x);
				gameDisplay.pause();
				return 0;
			}
			gameDisplay.outputText("Would you like to keep playing?",y,x);
			gameDisplay.outputText("Enter: 'y' for yes, 'n' for no.",y+1,x);
			while(1){
				char play = gameDisplay.getKey();
				if(play == 'n' || hplr.getMoney()==0)
					return 0;
				if(play == 'y')
					break;
			}
        }
        gameDisplay.potBanner(0);
        gameDisplay.moneyBanners(hplr.getMoney(), cplr.getMoney());
        if(hplr.getMoney()<=0)
        {
            gameDisplay.outputText("You are Bankrupt!! Better luck next time!",y+2,x);
            gameDisplay.pause();
            return 0;
            
        }
        gameDisplay.outputText("Would you like to keep playing?               ",y+3,x);
        gameDisplay.outputText("Enter: 'y' for yes, 'n' for no.",y+4,x);
        while(1){
            char play = gameDisplay.getKey();
			if(play == 'n')
				return 0;
			if(play == 'y')
				break;
        }
		playerBalance=playerBalance+hplr.getMoney();
	}
	return 0;
}//end of main

/*
 * This is the interrupt service routine called when the resize screen 
 * signal is captured.
 */
void pokerdetectResize(int sig) {
	// update the display class information with the new window size
    gameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
    signal(SIGWINCH, pokerdetectResize);
	/*INSERT YOUR OWN SCREEN UPDATE CODE instead of stub_PrintResize*/
	stub_PrintResize();
}

/*
 * This is a simple stub that should be replaced with what the game does
 * when the screen resizes. 
 */
void stub_PrintResize(void) {
	// gets the new screen size
	int cols = gameDisplay.getCols();
	int lines = gameDisplay.getLines();
	// setups a message stream
	stringstream messageString;
	messageString << "Terminal is " << cols << "x" << lines;
	// prints out the information of the new screen size in a top banner
	gameDisplay.bannerTop(messageString.str());
}

#endif
