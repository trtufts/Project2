#include <stdio.h>
#include <stdlib.h>
#include "p_player.h"
#include <iostream>
#include "display.h"


using namespace std;

player::player(double m){
    money = m;
}

player::~player(void){};
double player::getMoney(){
    return money;
};


void player::setMoney(double x){
	money = money + x;
}

double player::makeMove(int hmoney, display gameDisplay, int y, int x){
	double b;
	double temp=hmoney+1;
	char bcf;
	if(hmoney==0)return 0;
	while(bcf!='b' && bcf!='c' && bcf != 'f'){
            gameDisplay.outputText("Do you want to bet check or fold? Type b for bet, ",y+1,x);
            gameDisplay.outputText("c for check, or f for fold. ",y+2,x);
            bcf = gameDisplay.getKey();
	}
	if (bcf == 'c') {
		b=0;
		return b;
	}
	if (bcf == 'f') {
		b = -1;
		return b;
	}
	while(temp > hmoney || temp <= 0&&(temp==NULL))
		if (bcf == 'b') {
			temp = gameDisplay.getInput("Please enter a bet:\t");
		//if(temp >= hmoney || temp <= 0){
                //    temp = gameDisplay.getInput("Try again:\t");
               // }
	}
        b = temp;
	return b;
}


