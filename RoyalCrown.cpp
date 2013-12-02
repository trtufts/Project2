#include "display.h"
#include <signal.h>
#include <ncurses.h>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <stdio.h>

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
double gameTime1;
double gameTime2;
double gameTime3;

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
	gameTime1 = 0.0;
	gameTime2 = 0.0;
	gameTime3 = 0.0;
	
	// draw the initial game
	drawGame();
	
	// various variable declarations
	char key;
	int cardX = 0;
	int cardY = 0;
	int boxSizeY;
	
	// infinite loop for the main program, you can press ctrl-c to quit
	for (;;) {
		// calls the game display to capture some input
    	key = gameDisplay.captureInput();
		// if a mouse event occurred
		if (key == -1) {
			
			// record the location of the mouse event
			cardX = gameDisplay.getMouseEventX();
			cardY = gameDisplay.getMouseEventY();
			
			// check if it was a left click
			if (gameDisplay.getMouseEventButton()&LEFT_CLICK) {
				// Follow the correct option

				// used to define y-ranges
				boxSizeY = lines/5;
				
				// all valid options are within this x-range
				if( (cols/4 <= cardX) && (cardX <= 3*cols/4) ){
				
					// If the player clicks inside the game1 box
					if( (1 <= cardY) && (cardY <= boxSizeY) ){
						time(&gameStart);
						messageString.str("");
						messageString << "You have selected Game 1";
						gameDisplay.bannerTop(messageString.str());
						sleep(5);
						time(&gameEnd);
						gameTime1 += difftime(gameEnd, gameStart);
						drawGame();
					
					// If the player clicks inside the game2 box
					} else if( (2+boxSizeY <= cardY) && (cardY <= 1+2*boxSizeY) ){
						time(&gameStart);
						messageString.str("");
						messageString << "You have selected Game 2";
						gameDisplay.bannerTop(messageString.str());
						sleep(5);
						time(&gameEnd);
						gameTime2 += difftime(gameEnd, gameStart);
						drawGame();
					
					// If the player clicks inside the game3 box
					} else if( (3+2*boxSizeY <= cardY) && (cardY <= 2+3*boxSizeY) ){
						time(&gameStart);
						messageString.str("");
						messageString << "You have selected Game 3";
						gameDisplay.bannerTop(messageString.str());
						sleep(5);
						time(&gameEnd);
						gameTime3 += difftime(gameEnd, gameStart);
						drawGame();
					
					// If the player clicks inside the quit box
					} else if( (4+3*boxSizeY <= cardY) && (cardY <= 3+4*boxSizeY) ){
						break;
						
					// If the player doesn't click an option (y coordinate)
					} else {
						messageString.str("");
						messageString << "Please click on a valid option";
						gameDisplay.bannerTop(messageString.str());		
					}
				// If the player doesn't click an option (x coordinate) (caught first)
				} else {
					messageString.str("");
					messageString << "Please click on a valid option";
					gameDisplay.bannerTop(messageString.str());					
				}
				
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
	/*					
	printf("Thank you for playing!\n");
	printf("You have cashed out %d chips and played %d cards.\n", playerBalance, cardCount);
	*/
	
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
	// various formatting variables
	stringstream messageString;
	int spaceSize;
	
	// gets the screen size
	cols = gameDisplay.getCols();
	lines = gameDisplay.getLines();
	
	gameDisplay.eraseBox(0,0,cols,lines);
	
	int boxSizeX = cols/2;
	int boxSizeY = lines/5;
	
	// draws selection boxes
	gameDisplay.drawBox(cols/4, 1, boxSizeX, boxSizeY, 0);
	gameDisplay.drawBox(cols/4, 2+boxSizeY, boxSizeX, boxSizeY, 0);
	gameDisplay.drawBox(cols/4, 3+2*boxSizeY, boxSizeX, boxSizeY, 0);
	gameDisplay.drawBox(cols/4, 4+3*boxSizeY, boxSizeX, boxSizeY, 0);
	
	// adds text to screen

	// Game 1, Time 1
	messageString.str("");
	messageString << "Gin Rummy - Time Played: " << gameTime1;
	spaceSize = cols/4 + 1;
	mvprintw(1 + boxSizeY/2, spaceSize, "%s", messageString.str().c_str());
	
	// Game 2, Time 2
	messageString.str("");
	messageString << "Go Fish - Time Played: " << gameTime2;
	spaceSize = cols/4 + 1;
	mvprintw(2 + 3*boxSizeY/2, spaceSize, "%s", messageString.str().c_str());
	
	// Game 3, Time 3
	messageString.str("");
	messageString << "Poker - Time Played: " << gameTime3;
	spaceSize = cols/4 + 1;
	mvprintw(3 + 5*boxSizeY/2, spaceSize, "%s", messageString.str().c_str());
	
	// Quit
	messageString.str("");
	messageString << "Quit";
	spaceSize = cols/4 + 1;
	mvprintw(4 + 7*boxSizeY/2, spaceSize, "%s", messageString.str().c_str());

	
	if((lines < 18)||(cols < 65)){
		messageString.str("");
		messageString << "Please make the screen at least 65x18, it is currently " << cols << "x" << lines;
		gameDisplay.bannerTop(messageString.str());
	}
	
	// We draw the stats last to hide the cursor
	messageString.str("");
	messageString << "Player has " << playerBalance << " chips. Player has played a total of " << cardCount << " cards.";
	gameDisplay.bannerBottom(messageString.str());
}
