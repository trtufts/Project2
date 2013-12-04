/* Title: Project 1 ECE373 Display Class C++ File
 * Author: John Shield
 * Description: Defines the functionality of the user interface.
 *
 * NOTES:
 *		* Requires the terminal (Putty) to be set to UTF-8.
 *		* Does not function when running a screen session.
 */


//BRIAN HICKEY 2013














#include <iostream>
#include <sys/ioctl.h>
#include <cstdio>
#include <unistd.h>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include <sstream>



#include "display.h"

using namespace std;

/* Function: This is the constructor.
 * Description: It is called whenever an object of class display is initialized
 */
display::display(void) {
	/* Initilization of Terminal */
	// required to get card suits displaying, combined with UTF-8 set in terminal
	setlocale(LC_ALL,"en_US.utf-8");

	// initialize ncurses screen
	initscr();
	// allow for color settings
	start_color();
	// clear the screen
	clear();
	// turn off the keyboard echo (reqiured while drawing)
	noecho();
	// Change to character mode (so individual characters are being read at a
	// time rather than waiting for a carriage return).
	cbreak();
	// Allows for function keys to be used (also nessacary for getting the mouse
	// movement working).
	keypad(stdscr, TRUE);
	// set which mouse events are captured
	mousemask(ALL_MOUSE_EVENTS, NULL);
	// Setting the timeout for the capture input values are in 1/10ths of a second.
	halfdelay(5);

	curs_set(0);


	// setup the screen size settings.
	cols = 80;
    lines = 24;
	// this updates the locally stored col and line variables
	handleResize(0);
	// set a no card draw offset of 1 so the bottom banner is not overwritten
	lineBoundaryOffset = 1;

    init_pair(1, COLOR_CYAN, COLOR_BLACK); // for card outline
	init_pair(2, COLOR_BLUE, COLOR_BLACK); // for spades and clubs
	init_pair(3, COLOR_RED, COLOR_BLACK);  // for hearts and diamonds
	init_pair(4, COLOR_GREEN, COLOR_BLACK); // for turned over card
	init_pair(5, COLOR_GREEN, COLOR_BLACK); // for box drawing
	init_pair(6, COLOR_GREEN, COLOR_BLACK); // for banner display


}

/* Function: This is the destructor.
 * Description: This is called just before an object is deleted.
 */
display::~display() {
	// this is turns off all the special settings and returns the terminal to normal
	endwin();
	// insert deletion of dynamically created objects here too
}

/*
 * Function: This captures all the userinput.
 * Description: It captures mouse and keyboard events.
 * 		Returns "Positive Number"
 *			- for user keypress
 *			- this is a character code typed
 * 		Returns "0" - for no user input
 *			- this is when nothing is typed for half a second
 *			- allows for other timed operations to occur
 *		Returns "-1" - for mouse event
 *			- details of the mouse event must be fetched from this class
 *			- use getMouseEventX, getMouseEventY and getMouseEventButton
 */
int display::captureInput(void) {
	// obtain one mouse event or keypress
	int ch=getch();
    // this is a switch statement for the result of getch
	switch (ch) {
    case KEY_MOUSE: // this occurs when an mouse event occurs
      {
        MEVENT mevent; // this is a variable declared of type MEVENT
        getmouse(&mevent); // this gets the mouse event from ncurses (library)
		mouseEventX = mevent.x; // get the column location of the event
    	mouseEventY = mevent.y; // get the row location of the event
		mouseEventButton = mevent.bstate; // get the button state of the mouse
		return -1; // -1 is for a mouse event
      }
      break;
	case ERR: // this occurs when there is a timeout
	  {
		return 0; // 0 is when nothing occurs
	  }
	  break;
    default: // this occurs when a key is pressed
	  return ch; // a character is when the user types something
    }

	return 0; // this is never called, but is used to stop compiler complaints
}

/*
 * Function: Updates all the information in the display class on window resize
 * Description: This function just updates information, it requires the call
 *		from a static singal handler. Signal handlers service interrupts and require
 *		a static function to be called, because they are not part of the main
 * 		program control flow. The signal handler should be declared in the main
 *		class, because your game should redraw the display on a resize.
 */
void display::handleResize(int sig) {
#ifdef TIOCGSIZE // operating system dependant differences
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts); // get the information of the terminal
    cols = ts.ts_cols;
    lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts); // get the information of the terminal
    cols = ts.ws_col;
    lines = ts.ws_row;
#endif /* TIOCGSIZE */
	resizeterm(lines, cols); // sets the ncurses window size correctly
}

/*
 * Function: Displays various cards on the game screen
 * Description: This function displays various playing cards on the screen.
 *		The first two arguments are the x and y coordinates of the top left corner
 * 		of the card.
 *			The suit values are: 1=spades, 2=hearts, 3=clubs, 4=diamonds
 * 			The numbers are: 1=Ace, 2-10=2-10, 11=Jack, 12=Queen, 13=King, 14=Joker
 *		Any suit and number that do not match the valid numberrs generates a face down
 *		card.
 *			The printAtt allows for one or more any of the following display settings:
 *				A_NORMAL        Normal display (no highlight)
 *				A_STANDOUT      Best highlighting mode of the terminal.
 *				A_UNDERLINE     Underlining
 *				A_REVERSE       Reverse video
 *				A_BLINK         Blinking
 *				A_DIM           Half bright
 *				A_BOLD          Extra bright or bold
 *				A_PROTECT       Protected mode
 *				A_INVIS         Invisible or blank mode
 *				A_ALTCHARSET    Alternate character set
 *				A_CHARTEXT      Bit-mask to extract a character
 *				COLOR_PAIR(n)   Color-pair number n
 */
void display::displayginCard(int x, int y, int suit, int number, int printAtt) {

	// Ncurses drawing settings
	attron(COLOR_PAIR(1) | printAtt);

	// prevent draw if it off the screen
	if (x>=0 && y>=0 && x<cols-6 && y<lines-lineBoundaryOffset) {
		// print the top lines of the card
		mvprintw(y,x,"\u250c\u2500\u2500\u2500\u2500\u2510");
		//mvprintw(y,x,"      ");
		// the next 4 if statements prevent draw if it is over the bottom of the screen
		if (y<lines-1-lineBoundaryOffset) {
			move(y+1,x); // move command
			printFace(suit,number,0, printAtt); // call function to print card face
		}
		if (y<lines-2-lineBoundaryOffset) {
			move(y+2,x); // move command
			printFace(suit,number,1, printAtt); // call function to print card face
		}
		if (y<lines-3-lineBoundaryOffset) {
			move(y+3,x); // move command
			printFace(suit,number,2, printAtt); // call function to print card face
		}
		if (y<lines-4-lineBoundaryOffset) {
			// prints the bottom lines of the card
			mvprintw(y+4,x,"\u2514\u2500\u2500\u2500\u2500\u2518");
			//mvprintw(y+4,x,"      ");
		}
	}

	// Ncurses turn off the drawing settings
	attroff(COLOR_PAIR(1) | printAtt);
}

/*
 * Function: Print a single line of what is written on the card.
 * Description: This copies suit, number and printAtt from the calling function.
 *		Also includes what line of the card face is being drawn.
 */
void display::printFace(int suit, int number, int line, int printAtt) {
	// draw left edge of the card
	printw("\u2502");
	//printw(" ");

	if (suit==2 || suit==4) { // Red for Hearts and Diamonds
		attron(COLOR_PAIR(3) | printAtt);
	} else { // Black for Spades and Clover
		attron(COLOR_PAIR(2) | printAtt);
	}

	// this the display of the joker
	if (number==14) {
        if (line==0)
            printw("J%s  ", joker);
        if (line==1)
            printw("oker");
        if (line==2)
            printw("  J%s", joker);
	// this is the display for the cards with suits and numbers
	} else if (suit>=1 && suit <=4 && number>=1 && number<=13) {
		if (line==0) {
			printSuit(suit); // function to draw suit
			printNumber(number); // function to draw number
			if (number!=10)
				printw(" ");
			printw(" ");
		} else if (line==2) {
			if (number!=10)
                printw(" ");
            printw(" ");
			printNumber(number); // function to draw number
			printSuit(suit);	// function to draw suit
		} else {
			printw("    ");
		}
	// this is for a face down card
	} else {
		// the face down cards have a special color
		attron(COLOR_PAIR(4) | printAtt);
		if (line==0)
			printw("%s  %s", spades, hearts);
		if (line==1)
            printw(" SK ");
		if (line==2)
			printw("%s  %s", diamonds, clubs);
		attroff(COLOR_PAIR(1) | printAtt);
	}

	// turn on the card edge color settings
    attron(COLOR_PAIR(1) | printAtt);
	// print the right edge of the card
	printw("\u2502");
	//printw(" ");
}

/*
 * Function: Print the suit of the card
 * Description: This is just a look up table.
 */
void display::printSuit(int suit) {
	switch (suit) {
		case 1:
            printw("%s",spades);
            break;
		case 2:
            printw("%s",hearts);
            break;
		case 3:
            printw("%s",clubs);
            break;
		case 4:
            printw("%s",diamonds);
            break;
		default:
			printw(" ");
			break;
	}
}

/*
 * Function: Prints the number on the card
 * Description: This is just a look up table.
 */
void display::printNumber(int number) {
    switch (number) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
		case 9:
		case 10:
            printw("%i",number);
            break;
        case 1:
            printw("%c",'A');
            break;
        case 11:
            printw("%c",'J');
            break;
        case 12:
            printw("%c",'Q');
            break;
        case 13:
            printw("%c",'K');
            break;
        default:
            printw(" ");
            break;
    }
}

/*
 * Function: Erases a rectangle on the screen
 * Description: x,y is for the top left corner, sizeX and sizeY set
 * 			how big the square is.
 */
void display::eraseBox(int x, int y, int sizeX, int sizeY) {
	string strDraw;
	int yCount;
	int maxSizeX;

	// this limits the column size of the draw when it is over the edge
	// of the drawing area
    if (sizeX+x > cols)
        maxSizeX=cols-x;
    else
        maxSizeX=sizeX;

	// for the number of rows that need to be drawn
	for (yCount=0; yCount<sizeY;yCount++) {
		// if the box goes over the edge of the drawable screen
		// stop drawing by breaking the loop
		if (yCount+y > lines-lineBoundaryOffset || y < 0)
			break;
		// reset the line to be drawn
		strDraw = "";
		// check that x is not off the screen
		if (x<=cols && x >= 0) {
			// make a string needed for box width
			strDraw.append(maxSizeX,' ');
			// print the line of the box
			mvprintw(y+yCount,x,"%s",strDraw.c_str());
		}
	}
}

/*
 * Function: Draws a box on the screen
 * Description: x,y is for the top left corner, sizeX and sizeY set
 *          how big the square is. printAtt allows for changes in the
 *			display settings.
 */
void display::drawBox(int x, int y, int sizeX, int sizeY, int printAtt) {
	string strDraw;
    int ii;
    int yCount;

	// set the box setting colors on
	attron(COLOR_PAIR(5) | printAtt);

	// for the box height being drawn loop
    for (yCount=0; yCount<sizeY;yCount++) {
		// break loop if the drawing is offscreen
        if (yCount+y > lines-lineBoundaryOffset || y < 0)
            break;
		// if x is on the screen
        if (x<=cols) {
			strDraw = "";
			// for the box width loop
            for (ii=0;ii<sizeX;ii++){
				// stop drawing if the x is offscreen
                if (ii+x > cols || x < 0)
                    break;
				// first line
                if (yCount==0) {
                    if (ii==0) {
						strDraw.append("\u250c"); // left
                    } else if (ii==sizeX-1) {
						strDraw.append("\u2510"); // right
                    } else {
						strDraw.append("\u2500"); // middle
                    }
				// last line
                } else if (yCount==sizeY-1) {
                    if (ii==0) {
                        strDraw.append("\u2514"); // left
                    } else if (ii==sizeX-1) {
                        strDraw.append("\u2518"); // right
                    } else {
                        strDraw.append("\u2500"); // middle
                    }
				// other lines
                } else {
                    if (ii==0) {
                        strDraw.append("\u2502"); // left
                    } else if (ii==sizeX-1) {
                        strDraw.append("\u2502"); // right
                    } else {
                        strDraw.append(" "); // middle
                    }
                }
			}
			// print the line that was created
			mvprintw(y+yCount,x,"%s",strDraw.c_str());
        }
    }
	// turn off the attribute colors
	attroff(COLOR_PAIR(5) | printAtt);
}

/*
 * Function: Draws an invisible box on the screen
 * Description: x,y is for the top left corner, sizeX and sizeY set
 *          how big the square is. printAtt allows for changes in the
 *			display settings.
 */
void display::drawBoxInvis(int x, int y, int sizeX, int sizeY, int printAtt) {
	string strDraw;
    int ii;
    int yCount;

	// set the box setting colors on
	attron(COLOR_PAIR(9) | printAtt);

	// for the box height being drawn loop
    for (yCount=0; yCount<sizeY;yCount++) {
		// break loop if the drawing is offscreen
        if (yCount+y > lines-lineBoundaryOffset || y < 0)
            break;
		// if x is on the screen
        if (x<=cols) {
			strDraw = "";
			// for the box width loop
            for (ii=0;ii<sizeX;ii++){
				// stop drawing if the x is offscreen
                if (ii+x > cols || x < 0)
                    break;
				// first line
                if (yCount==0) {
                    if (ii==0) {
						strDraw.append("\u250c"); // left
                    } else if (ii==sizeX-1) {
						strDraw.append("\u2510"); // right
                    } else {
						strDraw.append("\u2500"); // middle
                    }
				// last line
                } else if (yCount==sizeY-1) {
                    if (ii==0) {
                        strDraw.append("\u2514"); // left
                    } else if (ii==sizeX-1) {
                        strDraw.append("\u2518"); // right
                    } else {
                        strDraw.append("\u2500"); // middle
                    }
				// other lines
                } else {
                    if (ii==0) {
                        strDraw.append("\u2502"); // left
                    } else if (ii==sizeX-1) {
                        strDraw.append("\u2502"); // right
                    } else {
                        strDraw.append(" "); // middle
                    }
                }
			}
			// print the line that was created
			mvprintw(y+yCount,x,"%s",strDraw.c_str());
        }
    }
	// turn off the attribute colors
	attroff(COLOR_PAIR(9) | printAtt);
}

/*
 * Function: Draws a banner of text at the bottom right of the screen
 * Description: Inverts the color and draws the banner at the bottom
 *		of the screen. Does not handle carriage returns on the string.
 */
void display::bannerBottom(string bannerText) {
	// change to the banner draw settings
	attron(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
	// checks if the banner string size is smaller than the width of the screen
    if((unsigned)cols > bannerText.size()) {
		// moves the cursor to the bottom of the screen
		move(lines-1,0);
		// fill in extra space to the banner text is right adjusted
        hline(' ',cols - bannerText.size());
		// prints out the banner text
		mvprintw(lines-1,cols-bannerText.size(),"%s", bannerText.c_str());
	// if banner string size is larger than width of screen
	} else {
		// clip the banner text so it doesn't wrap over to the next line
		mvprintw(lines-1,0,"%s", (bannerText.substr(0,cols)).c_str());
	}
	// turn off the draw colors
	attroff(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
}

void display::bannerBet(string bannerText) {
	// change to the banner draw settings
	attron(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
	// checks if the banner string size is smaller than the width of the screen
    if((unsigned)cols > bannerText.size()) {
		// moves the cursor to the bottom of the screen
		move(lines-2,0);
		// fill in extra space to the banner text is right adjusted
        hline(' ',cols - bannerText.size());
		// prints out the banner text
		mvprintw(lines-2,cols-bannerText.size(),"%s", bannerText.c_str());
	// if banner string size is larger than width of screen
	} else {
		// clip the banner text so it doesn't wrap over to the next line
		mvprintw(lines-2,0,"%s", (bannerText.substr(0,cols)).c_str());
	}
	// turn off the draw colors
	attroff(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
}

void display::bannerBetClear(string bannerText) {
	// change to the banner draw settings
	attron(COLOR_PAIR(7) | A_REVERSE | A_BOLD);
	// checks if the banner string size is smaller than the width of the screen
    if((unsigned)cols > bannerText.size()) {
		// moves the cursor to the bottom of the screen
		move(lines-2,0);
		// fill in extra space to the banner text is right adjusted
        hline(' ',cols - bannerText.size());
		// prints out the banner text
		mvprintw(lines-2,cols-bannerText.size(),"%s", bannerText.c_str());
	// if banner string size is larger than width of screen
	} else {
		// clip the banner text so it doesn't wrap over to the next line
		mvprintw(lines-2,0,"%s", (bannerText.substr(0,cols)).c_str());
	}
	// turn off the draw colors
	attroff(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
}

void display::backgroundWhite() {
	attron(COLOR_PAIR(8) | A_REVERSE | A_BOLD);
	for(int line = 0; line < lines; line++) {
		move(line,0);
		hline(' ',cols);
		mvprintw(line,cols,"%s", "");
	}
}

/*
 * Function: Draws a banner of text at the top left of the screen
 * Description: Inverts the color and draws the banner at the top
 *      of the screen. Does not handle carriage returns on the string.
 */
void display::bannerTop(string bannerText) {
	// change to the banner draw settings
	attron(COLOR_PAIR(7) | A_REVERSE | A_BOLD);
	// checks if the banner string size is smaller than the width of the screen
    if((unsigned)cols > bannerText.size()) {
		// moves the cursor to the bottom of the screen
		move(0,0);
		// prints out the banner text
		printw("%s", bannerText.c_str());
		// fill in extra space after the banner text
        hline(' ',cols - bannerText.size());
	// if banner string size is larger than width of screen
	} else {
		// clip the banner text so it doesn't wrap over to the next line
		mvprintw(0,0,"%s", (bannerText).c_str());
	}
	// turn off the draw colors
	attroff(COLOR_PAIR(7) | A_REVERSE | A_BOLD);
}

void display::displayText(string text, int locX, int locY) {

	if(locY > (unsigned)lines-1) {
		return;
	}

	if(locX + text.size() > (unsigned)cols-1) {
		return;
	}

	// change to the banner draw settings
	attron(COLOR_PAIR(7) | A_REVERSE | A_BOLD);
	// checks if the banner string size is smaller than the width of the screen
    if((unsigned)cols > text.size()) {
		// moves the cursor to the bottom of the screen
		move(locY,locX);
		// prints out the banner text
		printw("%s", text.c_str());
		// fill in extra space after the banner text
        hline(' ',cols - text.size());
	// if banner string size is larger than width of screen
	} else {
		// clip the banner text so it doesn't wrap over to the next line
		//mvprintw(locY,locX,"%s", (text).c_str());
	}
	//turn off the draw colors
	attroff(COLOR_PAIR(7) | A_REVERSE | A_BOLD);
}

void display::clearDisplay() {
	clear();
}





















void display::displayHumCards(int *cardsInHand) {
        int x = 30;
        int y = 26;
        int suit, number, i, card;
        for(i=0; i<52; i++){
                if(cardsInHand[i] != -1){
                        card = cardsInHand[i];
                        number = card%13;
                        if(number == 0){
                                number = 13;
                                suit = (card/13)+1;
                        }
                        else
                                suit = card/13;
                        displayCard(x, y, suit+1, number, A_BOLD);
                        x += 6;
                }
                else if(cardsInHand[i] == -1)
                ;
        }
}

void display::displayP1Cards(int *cardsInHand) {
        int x = 30;
        int y = 31;
        int suit, number, i, card;
        for(i=0; i<52; i++){
                if(cardsInHand[i] != -1){
                        card = cardsInHand[i];
                        number = card%13;
                        if(number == 0){
                                number = 13;
                                suit = (card/13)+1;
                        }
                        else
                                suit = card/13;
                        displayCard(x, y, suit+1, number, A_BOLD);
                        x += 6;
                }
                else if(cardsInHand[i] == -1)
                ;
                        //break;
        }
}

void display::displayPair(int x, int y, int suit, int number, int printAtt) {
        displayCard(x, y, suit, number, printAtt);
        displayCard(x-1, y-1, suit, number, printAtt);
}

void display::updateScreen(int deckCards, int comp1Cards,
int comp2Cards, int comp3Cards, int *comp1Score, int *comp2Score,
int *comp3Score, int *humanScore){
        int comp1score = 0;
        int comp2score = 0;
        int comp3score = 0;
        int humanscore = 0;
        for(int i=0; i<13; i++){
                if(comp1Score[i] == 1)
                        comp1score++;
                if(comp2Score[i] == 1)
                        comp2score++;
                if(comp3Score[i] == 1)
                        comp3score++;
                if(humanScore[i] == 1)
                        humanscore++;
        }
        displayCard(57,18,5,0,A_BOLD);
        mvprintw(20,65, "Remaining Cards: %d", deckCards);
        mvprintw(5,65, "Computer 2");
        mvprintw(8,73, "Cards: %d", comp2Cards);
        mvprintw(11,67, "Score: %d", comp2score);
        mvprintw(15,7, "Computer 1");
        mvprintw(19,14, "Cards: %d", comp1Cards);
        mvprintw(22,8,"Score: %d", comp1score);
        mvprintw(15,113, "Computer 3");
        mvprintw(18, 121, "Cards: %d", comp3Cards);
        mvprintw(21, 115, "Score: %d", comp3score);
        mvprintw(2,67, "GO FISH");
        mvprintw(24,65, "Player");
        mvprintw(25,65, "Score: %d", humanscore);
        displayCard(8, 17, 5, 0 , A_BOLD);
        displayCard(67,6,5,0,A_BOLD);
        displayCard(115,16,5,0,A_BOLD);
        mvprintw(36,0, "\n");
        refresh();
}




void display::displayCard(int x, int y, int suit, int number, int printAtt) {

	// Ncurses drawing settings
	attron(COLOR_PAIR(1) | printAtt);
	// prevent draw if it off the screen
	if (x>=0 && y>=0 && x<cols-6 && y<lines-lineBoundaryOffset) {
		// print the top lines of the card
		mvprintw(y,x,"\u250c\u2500\u2500\u2500\u2500\u2510");
		// the next 4 if statements prevent draw if it is over the bottom of the screen
		if (y<lines-1-lineBoundaryOffset) {
			move(y+1,x); // move command
			printFace(suit,number,0, printAtt); // call function to print card face
		}
		if (y<lines-2-lineBoundaryOffset) {
			move(y+2,x); // move command
			printFace(suit,number,1, printAtt); // call function to print card face
		}
		if (y<lines-3-lineBoundaryOffset) {
			move(y+3,x); // move command
			printFace(suit,number,2, printAtt); // call function to print card face
		}
		if (y<lines-4-lineBoundaryOffset) {
			// prints the bottom lines of the card
			mvprintw(y+4,x,"\u2514\u2500\u2500\u2500\u2500\u2518");
		}
	}
	// Ncurses turn off the drawing settings
	attroff(COLOR_PAIR(1) | printAtt);
}




void display::dividerBanner() {
	// change to the banner draw settings
	attron(COLOR_PAIR(7) | A_REVERSE | A_BOLD);

	//move cursor to halfway and draw divider
	move(double(lines)/2-1,0);
	int column = double(cols)-double(cols)*.3;
	hline(' ',column);

	//makes the vertical divider
	for(int i = 0; i <= cols; i++)
	{
		mvprintw(i,column, "%s","  ");
	}

	//makes the divider for the message update
	//move(double(lines)-double(lines)*.1,column);
	//hline(' ',column);

	//makes the divider for the pot
	move(double(lines)*.15,column);
	hline(' ',column);

	// turn off the draw colors:
	attroff(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
	move(double(lines)/2+lines*.1,column/2-8);
	printw("%s", "Computer Player");
	// prints out the banner text
	move(lines*.1,column/2-7);
	printw("%s", "Human Player");
}
void display::potBanner(double pot){
	string s = "The Pot:            $";
	move(3, cols-45);
	printw("%s%.2f", s.c_str(),pot);
}

void display::adBanner(string ad){
	move(1, 1);
	printw("%s", ad.c_str());
}

void display::moneyBanners(double hum, double comp)
{
	int column = double(cols)-double(cols)*.3;
	move(double(lines)/2+lines*.15,column/2-5);
	printw("%c%.2f",'$', comp);

	// prints out the banner text
	move(lines*.15,column/2-5);
	printw("%c%.2f",'$', hum);
}
void display::winBanner(string bannerText)
{

	mvprintw(lines-25,cols-bannerText.size()-25,"%s", bannerText.c_str());
}
void display::outputText(string bannerText, int y, int x)
{
	move(y,x);
	printw("%s", bannerText.c_str());
}
void display::clearText()
{
	int y = double(lines)*.15+3;
	for(int i = y; i <= lines-1; i++)
	{
		int column = double(cols)-double(cols)*.3;
		move(i,column+5);
		hline(' ',cols);
	}
}
void display::moveCursur(int y, int x)
{
    move(y,x);
}

void display::pause()
{
    char key;
    for(;;){
        move(lines-3,cols-45);
        printw("Please click a key to continue...");
        key = this->captureInput();
        if(key >=-1){
            break;
        }
    }
    move(lines-3,cols-45);
    printw("                                 ");
}
char display::getKey()
{
    char key;
    move(lines-3,cols-45);
    hline(' ',cols);

    for(;;){
        move(lines-3,cols-45);
        printw("Please enter your response...    ");
        key = this->captureInput();
        if(key>0){
			return key;
        }
    }
}
string display::getKey1(int n)
{
    int i = 0;
    string s = "";
    char key;
    move(lines-3,cols-45);
    hline(' ',cols);

    for(;;){
        string temp = "";
        move(lines-3,cols-45);
        printw("Please enter your response...    ");
        key = this->captureInput();
        if(key=='1'||key=='2'||key=='3'||key=='4'||key=='5'){
			stringstream ss;
			ss << key;
			ss >> temp;
			s = s+temp;
			printw("%s", s.c_str());
			i++;
        }
        if(i==n){
			stringstream st;
			st >> temp;
			s = s+ temp;
			return s;
		}
    }
}
double display::getInput(string message)
{

	double d;
	char key;
	string s;
	move(lines-3,cols-45);
	hline(' ',cols);

	for(;;)/* if valid input was not entered */
	{
		string temp;
		move(lines-3,cols-45);
		printw("%s", message.c_str());
		key = this->captureInput();
		if((key >=48 && key <= 57) || (key == 46)){
			stringstream ss;
			ss << key;
			ss >> temp;
			s = s+temp;
			printw("%s", s.c_str());
		}
		else if(key == '\n'){
			stringstream st;
			st << '\0';
			st >> temp;
			s = s+ temp;
			break;
		}
	}
	printw("%s", s.c_str());
	stringstream su(s);
	su >> d;
	return d;
}







































