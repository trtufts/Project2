#include <iostream>
#include <stdlib.h>                                                                           
#include "p_humanPlayer.h"

using namespace std;

humanPlayer::humanPlayer(double m): player(m){};

humanPlayer::~humanPlayer(void){};

int humanPlayer::replaceCards(display gameDisplay, int line, int x){
        int numOfCards = 0;
        char choice;
        while(1){
            gameDisplay.outputText("Do you want to replace any of your cards?",line+1,x);
            gameDisplay.outputText("Enter: 'y' for yes, 'n' for no.",line+2,x);
            choice = gameDisplay.getKey();
            if(choice == 'y'|| choice=='n')
                break;
        }
        if(choice =='y' && choice != 'n'){
        while(numOfCards<1||numOfCards>4){//checks for legal move
            gameDisplay.outputText("How many cards would you like to replace? You",line+4,x);
            gameDisplay.outputText("can replace up to 3 cards, or 4 cards if you",line+5,x);
            gameDisplay.outputText("have an Ace. Enter a number 1-4.",line+6,x);
            choice = gameDisplay.getKey();
            numOfCards = choice - '0';
            }
        }
            return numOfCards;
}
    int* humanPlayer::chooseCards(int n,display gameDisplay, int y, int x){
        int count = 0;
        static int temp[] = {0,0,0,0};
        string s;
        char index;
        if(n!=0){
            gameDisplay.outputText("Which card would you like to replace? Choose an",y+1,x);
            gameDisplay.outputText("index 1-5 corresponding to the cards on your",y+2,x);
            gameDisplay.outputText("screen '1' is the leftmost, '5' is the rightmost.",y+3,x);
            s = gameDisplay.getKey1(n);
        }
        while(count<n){
            index = s[count];
            temp[count]=index-'0';
            count++;
        }

        return temp;
    }
/****************** human player driver*************************/
void humanPlayer::humanPlayerDriver(void){
	humanPlayer p(0);
        cout<<"player input output tests"<<endl;
        display disp;
        int n = p.replaceCards(disp, 20, 40);
        cout<<"number  entered: "<<n<<endl;
        int *t;
        t = p.chooseCards(n,disp,30,40);
        cout<<"cards chosen: "<<endl;
        for(int i =0; i<4; i++)
                cout<<t[i]<<endl;
	cout<<"player make move test (initial money = 100): "<<endl;
	cout<<"if 0, you entered c, if -1, you entered f, and if > 0, you entered b: "<<endl;
	int b = p.makeMove(100,disp, 40, 40);
	cout<<"result: "<<b<<endl;
}
