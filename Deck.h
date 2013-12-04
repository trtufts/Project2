
//
//  Deck.h
//  Code
//
//  Created by Divya Reddy on 10/29/13.
//  Copyright (c) 2013 Divya Reddy. All rights reserved.
//

#ifndef __Code__Deck__
#define __Code__Deck__

#include <iostream>
using namespace std;

class Card{
public:
    Card(int value);
    
private:
    string mysuit;
private:int cardVal;
};

class Deck{
public:
	Deck();
    void ShuffleCards(int *cardsinDeck);
    int drawCard(int *cardsinDeck);
    
private:
    
};

#endif /* defined(__Code__Deck__) */
