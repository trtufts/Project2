// Player.cpp
// Player
//
// Created by James Danis

// Name of Class: Player Class
// Purpose: Instantiate each player of the game and manage cards in hand and cards placed in a scoring pile

#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Player::Player(void) {
 // int cardsInHand[52];                                          //Maximum amount of cards in a deck
  for(int i=0; i<52; i++)                                       //For every cell in cardsInHand array
    cardsInHand[i] = -1;                                        //Initialize value to -1 (meaning NULL)
  int scorePile[13];                                            //Maximum number of piles in scoring bin
  for(int i=0; i<13; i++)                                       //For every cell in cardsInPile array
    scorePile[i] = 0;                                           //Initialize to -1 (meaning NULL)
}

Player::~Player() {};                                           //Create deconstructor class

int Player::getCard(int cardValue) {                            //Method removes and returns all cards of input face value
  int cardsToGive = 0;                                          //Variable for returning cards in player's hand
  int idx = 1;                                                  //Indexer for storing cards to be given away
  for(int i=0; i<52; i++) {                                     //Loop through every cell of cardsInHand
    if(((cardsInHand[i]%13)+1) == cardValue) {                  //If face value of card being examined matches card asked for
      cardsToGive += cardsInHand[i]*idx;                        //Add card to variable storing cards given away
      idx *= 100;                                               //Increase idx to next slot to store another card
      cardsInHand[i] = -1;                                      //Nullify card in hand
    }
  }
  return cardsToGive;                                           //Return variable storing returned cards
}

void Player::addCard(int cardValue) {                           //Method adds a card to current player's hand
  if (cardValue <= 0)                                           //If no card was passed into method
    return;                                                     //Exit method
  int card1 = cardValue%100;                                    //Retrieve value of first card
  if(card1 > 0) {                                               //If variable is a valid card entry
    for(int i=0; i<52; i++) {                                   //Loop through every cell in cardsInHand
      if(cardsInHand[i] == -1) {                                //If cell being examined is empty
        cardsInHand[i] = card1;                                 //Place new card in this spot
        break;                                                  //Card has been placed, break out of loop
      }
    }
  }
  int card2 = (cardValue/100)%100;                              //Retrieve value of second card
  if(card2 > 0) {                                               //If variable is a valid card entry
    for(int i=0; i<52; i++) {                                   //Loop through every cell in cardsInHand
      if(cardsInHand[i] == -1) {                                //If cell being examined is empty
        cardsInHand[i] = card2;                                 //Place new card in this spot
        break;                                                  //Card has been placed, break out of loop
      }
    }
  }
  int card3 = cardValue/10000;                                  //Retrieve value of third card
  if(card3 > 0) {                                               //If variable is a valid card entry
    for(int i=0; i<52; i++) {                                   //Loop through every cell in cardsInHand
      if(cardsInHand[i] == -1) {                                //If cell being examined is empty
        cardsInHand[i] = card3;                                 //Place new card in this spot
        break;                                                  //Card has been placed, break out of loop
      }
    }
  }
  int scoreTest[13];                                            //Variable checks to see if any cards can be scored
  for(int i=0; i<13; i++)                                       //Loops through every cell in array
    scoreTest[i] = 0;                                           //Initializes value to zero
  int faceVal;                                                  //Variable for face value on card
  for(int i=0; i<52; i++) {                                     //Loops through every cell in cardsInHand
    if(cardsInHand[i] > 0) {                                    //If card being examined is valid
      faceVal = cardsInHand[i]%13;                              //Get face value of current card
      scoreTest[faceVal]++;                                     //Increment number of occurences of this card
    }
  }
  for(int i=0; i<13; i++) {                                     //Loop through each cell in scoreTest
    if(scoreTest[i] == 4) {                                     //If 4 cards of a face value are held in hand
      scorePile[i] = 1;                                         //Place these 4 cards in score pile
      for(int j=0; j<52; j++) {                                 //Loop through array of cards in hand
        if(cardsInHand[j] > 0) {                                //If a valid card is contained in this cell
          if((cardsInHand[j]%13) == i)                          //If current card is of scoring face value
            cardsInHand[j] = -1;                                //Remove from cards held in hand
        }
      }
    }
  }
}

