//Display Stub,  fully functional except captureInput feeds a string of values (added variable to display to handle this

#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncursesw/ncurses.h>
#include <iostream>
#include <cstdio>


using namespace std;

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

const char joker[]	  = {0xE2, 0x98, 0xBA, 0};
const char clubs[]    = {0xE2, 0x99, 0xA3, 0};
const char diamonds[] = {0xE2, 0x99, 0xA6, 0};
const char hearts[]   = {0xE2, 0x99, 0xA5, 0};
const char spades[]   = {0xE2, 0x99, 0xA0, 0};

class display {
public:

	display(void);

	~display(); // destructor

	// captures user input
	int captureInput(void);
	// stores new screensize on update
	void handleResize(int sig);

	/*
	 * Drawing commands
     */
    // display a card on the screen
	void displayCard(int x, int y, int suit, int number, int printAtt);
	// erase in the shape of a box on the screen
	void eraseBox(int x, int y, int sizeX, int sizeY);
	// draw a box on the screen
	void drawBox(int x, int y, int sizeX, int sizeY, int printAtt); 
	// display banner text at the bottom of the screen
	void bannerBottom(string bannerText);
	// display banner text at the top of the screen
	void bannerTop(string bannerText);

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
	int mouseEventFeed;
	int lineBoundaryOffset;
};

#endif


