//  Deck.cpp
//  Deck
//
//  Created by Divya Reddy on 10/26/13.
//  Copyright (c) 2013 Divya Reddy. All rights reserved.

//Name of Class: Deck Class
//Purpose:  To create the array of cards that will be played. To create a function that distributes the cards to each of players, a function that draws a card from the deck,
#include "Deck.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

Card::Card(int value){
    value=value;
    
    if (value>0 && value <=13){                     //Determining if the card value is less than of equal to 12, if it is
        mysuit = "Heart";                           //then it is Heart and contains the value from 1 to 12
        cardVal =value;
    }
    else if(value >13 && value <=26){              //If the card value is from 13 to 25 then it is a "Club"
        mysuit = "Club";
        cardVal = value%13;
    }
    else if(value>26 && value <=39){               //if the card value is from 26 to 38 then it is "Diamonds
        mysuit ="Diamonds";
        cardVal = value %13;
    }
    else if( value >39 && value <=52){             //if the card value is from 39 to 52 then it is " Spades"
        mysuit ="Spades";
        cardVal = value % 13;
    }
};


Deck::Deck(){                                      //Function that creates the deck of cards by creating an array of Cards
//    for(int i=0; i<53; i++)                        // that has values from 0 to 52. We will be only using the value from 1
  //      cardsinDeck[i] = i+1;                       // to 52
}

void Deck::ShuffleCards(int *cardsinDeck){                     //A void function that shuffles the cards in Deck
    random_shuffle(&cardsinDeck[0],&cardsinDeck[51]);
}

int Deck::drawCard(int *cardsinDeck) {                       // Draw Card function that returns the the first card in the deck pile
    int returnCard;                             // returns card number
    for(int i=0; i<53; i++) {                   // for loop that goes through the pile
        if((cardsinDeck[i] != -1)) {              // checks and sees when it reaches the card that does not have the value -1
            returnCard = cardsinDeck[i];        //returns that card card value
            cardsinDeck[i] = -1;                //sets the card value returned to -1
            return returnCard;                  // returns the card value
        }
    }
    return -1;
}

