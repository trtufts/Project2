/* Title: Project 1 ECE373 Display Class Header File
 * Author: John Shield
 * Description: Defines constants and class prototypes and variables
 */

// These are include files they are used for accessing functions and
// variables in external libraries.
#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncursesw/ncurses.h>
#include <iostream>
#include <cstdio>
#include <string>

// This is the namespace std, without this you would need to add "std::"
// infront of every variable and function from the std library.
using namespace std;

// These Mouse Mask Definitions are for some of the common mouse buttons
// that are used in this project.
#define LEFT_UP    1
#define LEFT_DOWN  2
#define LEFT_CLICK 4
#define LEFT_DOUBLECLICK 24

#define RIGHT_UP    4096
#define RIGHT_DOWN  8192
#define RIGHT_CLICK 16384
#define RIGHT_DOUBLECLICK 32768

#define MIDDLE_ROLLUP    1048576
#define MIDDLE_ROLLDOWN  256

// Some extended character definitions for showing the special symbols
// in the extended UTF-8 character map.
const char joker[]	  = {0xE2, 0x98, 0xBA, 0};
const char clubs[]    = {0xE2, 0x99, 0xA3, 0};
const char diamonds[] = {0xE2, 0x99, 0xA6, 0};
const char hearts[]   = {0xE2, 0x99, 0xA5, 0};
const char spades[]   = {0xE2, 0x99, 0xA0, 0};

/*
 * This is the display class definitions
 */
class display {
public:
	/* "constructor"
	* This function is called whenever a new object of class display is first
	* created. Put initialization functions in here.
	*/
	display(void);
	/* "destructor"
	* This function is called just before a object is deleted. Put clean up
	* functions in here.
	*/
	~display(); // destructor

	// captures user input
	int captureInput(void);
	// stores new screensize on update
	void handleResize(int sig);




	        void displayPair(int x, int y, int suit, int number, int printAtt);
        void displayHumCards(int *cardsInHand);
        void displayP1Cards(int *cardsInHand);
        void updateScreen(int deckCards, int comp1Cards, int
comp2Cards,int comp3Cards, int *comp1Score, int *comp2Score, int
*comp3Score, int *humanScore);

	void dividerBanner();
	void potBanner(double pot);
	void adBanner(string ad);
	void moneyBanners(double hum, double comp);
	void winBanner(string bannerText);
	void outputText(string bannerText, int y, int x);
	void clearText();
	void moveCursur(int y, int x);
	void pause();
	char getKey();
	string getKey1(int n);
	double getInput(string message);










	string bannerArray[20];
	int bannerIndex;

	/*
	 * Drawing commands
     */


    void displayCard(int x, int y, int suit, int number, int printAtt);


    // display a card on the screen
	void displayginCard(int x, int y, int suit, int number, int printAtt);
	// erase in the shape of a box on the screen
	void eraseBox(int x, int y, int sizeX, int sizeY);
	// draw a box on the screen
	void drawBox(int x, int y, int sizeX, int sizeY, int printAtt);
	// draw an invisible box on the screen
	void drawBoxInvis(int x, int y, int sizeX, int sizeY, int printAtt);
	// display banner text at the bottom of the screen
	void bannerBottom(string bannerText);

	void bannerBet(string bannerText);
	void bannerBetClear(string bannerText);
	void backgroundWhite();

	// display banner text at the top of the screen
	void bannerTop(string bannerText);

	void displayText(string text, int locX, int locY);

	// get information about the display
	int getCols(void) {return cols;}
	int	getLines(void) {return lines;}
	int getMouseEventX(void) {return mouseEventX;}
    int getMouseEventY(void) {return mouseEventY;}
    int getMouseEventButton(void) {return mouseEventButton;}

	// Updates the screen after you finish drawing
	void updateScreen(void) {refresh();}

	// sets an offset for when cards clip the bottom of the screen
	void setBottomOffset(int offset) {lineBoundaryOffset=offset;}

	void clearDisplay();
private:
	// These are private functions and variables used inside of display.
	// You should not try to access these from outside the display class.
	void printFace(int suit, int number, int line, int printAtt);
	void printSuit(int suit);
	void printNumber(int number);

	int cols;
	int lines;
	int mouseEventX;
	int mouseEventY;
	int	mouseEventButton;
	int lineBoundaryOffset;
};

#endif
