//Player.h
//Header file for  Player
//
//Created by James Danis

#ifndef __Player__Player__
#define __Player__Player__

#include <iostream>

class Player{
public:
   int cardsInHand[52];
   int scorePile[13];
   Player();
   ~Player();

   void addCard(int cardValue);
   int getCard(int cardValue);
private:
};

#endif
