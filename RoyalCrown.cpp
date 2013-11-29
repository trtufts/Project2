#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <time.h>


using namespace std;
display gameDisplay;
int cardCount;
int playerBalance;

static void detectResize (int sig); 
void redrawGame(void);

int main(int argc, char* argv[]){
	
	stringstream messageString;
	
	signal(SIGWINCH, detectResize); // enable the window resize signal
	
	// various variable declarations
	char key;
	int cardX = 0;
	int cardY = 0;
	int suit = 0;
	int number = 0;

	int dragX = 0;
	int dragY = 0;
	
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
			// Some of the mouse click values are defined in display.h
			// check if it was a left click
			if (gameDisplay.getMouseEventButton()&LEFT_CLICK) {
				// draw a random card at the click location
				suit = rand()%5;
				number = rand()%15;
				gameDisplay.displayCard(cardX,cardY,suit,number, A_BOLD);
			// check if it was a right click
			} else if (gameDisplay.getMouseEventButton()&RIGHT_CLICK) {
				// erase a portion of the screen in the shape of a card
				gameDisplay.eraseBox(cardX,cardY,6,5);
			// check for the start of a drag click
			} else if (gameDisplay.getMouseEventButton()&LEFT_DOWN) {
				// record start of the drag
				dragX = cardX;
				dragY = cardY;
			// when the mouse is released
			} else if (gameDisplay.getMouseEventButton()&LEFT_UP) {
				// calculate size of the drag
				int sizeX = abs(dragX-cardX);
				int sizeY = abs(dragY-cardY);
				// get to the top left corner of the drag area
				if (dragX > cardX)
					dragX = cardX;
                if (dragY > cardY)
                    dragY = cardY;
				// draw a box around the drag area
				gameDisplay.drawBox(dragX, dragY, sizeX, sizeY, 0);
			}
		// if a key was pressed
		} else if(key > 0) {
			// make bottom a banner message saying that a key was pressed
			messageString.str("");
			messageString << "Key " << key << " pressed";
			gameDisplay.bannerBottom(messageString.str());
		}
	}

	return 0;
}


void detectResize(int sig) {
	// update the display class information with the new window size
    gameDisplay.handleResize(sig);
	// re-enable the interrupt for a window resize
    signal(SIGWINCH, detectResize);

	redrawGame();
}

void redrawGame(void) {
	// gets the new screen size
	int cols = gameDisplay.getCols();
	int lines = gameDisplay.getLines();
	
	
	
	// Tells the user that the resize was a success
	stringstream messageString;
	messageString << "Resize successful, Terminal is now " << cols << "x" << lines;
	gameDisplay.bannerTop(messageString.str());
}