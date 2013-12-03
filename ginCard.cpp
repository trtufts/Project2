//ginCard.cpp
#include "ginCard.h"

ginCard::ginCard(int a, int b, int c, bool d){
	card = a;
	value = b;
	suit = c;
	deadwood = d;
}

ginCard::ginCard(){
	card;
	value;
	suit;
	deadwood;
}

ginCard::~ginCard(){
};
