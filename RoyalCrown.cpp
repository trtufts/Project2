#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <time.h>

/*
#include GAME1
#include GAME2
#include GAME3
*/

using namespace std;
display gameDisplay;
int cardCount;
int playerBalance;
int cols;
int lines;

static void detectResize (int sig); 
void drawGame(void);

int main(int argc, char* argv[]){
	
	// initialize the global variables
	cardCount = 0;
	playerBalance = 1000;
	
	// declare a stringstream to be used for various messages
	stringstream messageString;
	
	// enable the window resize signal
	signal(SIGWINCH, detectResize);
	
	// various timer variables
	time_t gameStart;
	time_t gameEnd;
	double gameTime1 = 0;
	double gameTime2 = 0;
	double gameTime3 = 0;
	
	// draw the initial game
	drawGame();
	
	// various variable declarations
	char key;
	int cardX = 0;
	int cardY = 0;
	
	// infinite loop for the main program, you can press ctrl-c to quit
	for (;;) {
		// calls the game display to capture some input
    	key = gameDisplay.captureInput();
		// if a mouse event occurred
		if (key == -1) {
			// make a banner message
			messageString.str("");
			messageString << "A mouse event occurred x=" \
				<< gameDisplay.getMouseEventX() << ", y=" \
				<< gameDisplay.getMouseEventY() << ", bstate=" \
				<< gameDisplay.getMouseEventButton();
			// display a banner message
			gameDisplay.bannerTop(messageString.str());
			
			// record the location of the mouse event
			cardX = gameDisplay.getMouseEventX();
			cardY = gameDisplay.getMouseEventY();
			
			// check if it was a left click
			if (gameDisplay.getMouseEventButton()&LEFT_CLICK) {
				// Follow the correct option
			// check if it was a right click
			} else if (gameDisplay.getMouseEventButton()&RIGHT_CLICK) {
				// Reject the Right Mouse click
				messageString.str("");
				messageString << "Please left click instead of right clicking";
				gameDisplay.bannerTop(messageString.str());
			// check for the start of a drag click
			} else if (gameDisplay.getMouseEventButton()&LEFT_DOWN) {
				// Do nothing at the start of the drag
			// when the mouse is released
			} else if (gameDisplay.getMouseEventButton()&LEFT_UP) {
				// Reject the drag
				messageString.str("");
				messageString << "Please left click instead of drag clicking";
				gameDisplay.bannerTop(messageString.str());
			}
		// if a key was pressed
		} else if(key > 0) {
			// Make bottom a banner message saying that a key was pressed and ask for a mouse click
			messageString.str("");
			messageString << "Key " << key << " pressed, Please use the mouse to select an option.";
			gameDisplay.bannerTop(messageString.str());
		}
	}

	return 0;
}


void detectResize(int sig) {
	// update the display class information with the new window size
    gameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
    signal(SIGWINCH, detectResize);

	drawGame();
}

void drawGame(void) {
	stringstream messageString;
	// gets the screen size
	cols = gameDisplay.getCols();
	lines = gameDisplay.getLines();
	
	gameDisplay.eraseBox(0,0,cols,lines);
	
	messageString.str("");
	messageString << "Player has " << playerBalance << " chips. Player has played a total of " << cardCount << " cards.";
	gameDisplay.bannerBottom(messageString.str());
	
	int boxSizeX = cols/2;
	int boxSizeY = lines/5;
	
	gameDisplay.drawBox(cols/4, 1, boxSizeX, boxSizeY, 0);
	gameDisplay.drawBox(cols/4, 2+boxSizeY, boxSizeX, boxSizeY, 0);
	gameDisplay.drawBox(cols/4, 3+2*boxSizeY, boxSizeX, boxSizeY, 0);
	gameDisplay.drawBox(cols/4, 4+3*boxSizeY, boxSizeX, boxSizeY, 0);
	
	// Tells the user that the draw was a success, remove after testing
	messageString.str("");
	messageString << "Draw successful, Terminal is now " << cols << "x" << lines;
	gameDisplay.bannerTop(messageString.str());
	
	if((lines < 18)||(cols < 65)){
		messageString.str("");
		messageString << "Please make the screen at least 65x18, it is currently " << cols << "x" << lines;
		gameDisplay.bannerTop(messageString.str());
	}
}