#include <stdio.h>
#include <stdlib.h>
#include "p_pot.h"
using namespace std;
pot::pot(double i){
    potTotal = i;
}
pot::~pot(void){};

double pot::getPot(void){
    return potTotal;
                    }
void pot::inputToPot(double i){
    if(i>0) potTotal += i;
                    }
void pot::resetPot(){
    potTotal = 0;
}
