#include <stdio.h>
#include <stdlib.h>
#include "p_card.h"

using namespace std;

card::card(int s, int n)
{
    suit = s;
    number = n;
}

card::card(void)
{ //the null card
        suit =0;
        number =0;
}

card::~card(void){};

int card::getSuit() const
{
        return suit;
}

int card::getNumber() const
{
        return number;
}
void card::setValues(int s, int n)
{
    suit = s;
    number = n;
}
