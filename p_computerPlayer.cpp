/*
#include "p_Player.h"
#include "p_ComputerPlayer.h"

ComputerPlayer::public Player();

ComputerPlayer::~Player();

double ComputerPlayer::determineBet(Hand* currentHand, double humanBet) //this function determines how much the comptuer is going to bet
{
int handScore = currentHand.scoreHand(); //gets the hand score
	switch(handScore) 
		{
		//if Royal Flush, all in
		case 10:
			return money;
			
		case 9: //if Straight Flush, all in
			return money;
			
		case 8: //if 4 of a kind, bet 75% of comp's $$
			if((money*0.75)>humanBet)
				return (money*0.75);
			else //if 75% is less than humanBet, all in or match
				if(humanBet>money)
					return money;
				else
					return humanBet;
					
		case 7: //if Full House, bet 50% of comp's $$ or match human
			if((money*0.5)>humanBet)
				return (money*0.5);
			else //if 50% is less than humanBet, all in or match
				if(humanBet>money)
					return money;
				else
					return humanBet;
					
		case 6: //if flush, bet 50% of comp's $$ or match human
			if((money*0.5)>humanBet)
				return (money*0.5);
			else //if 50% is less than humanBet, all in or match
				if(humanBet>money)
					return money;
				else
					return humanBet;
				
		case 5: //if straight, bet 25% or match human
			if((money*0.25)>humanBet)
				return (money*0.25);
			else //if 25% is less than humanBet, all in or match
				if(humanBet>money)
					return money;
				else
					return humanBet;
				
		case 4: //if 3 of a kind, match human
			if(money<humanBet)
				return money;		
			return humanBet;
			
		case 3: //if 2 pair, match human
			if(money<humanBet)
				return money;		
			return humanBet;
			
		case 2: //if pair, match human
			if(money<humanBet)
				return money;
			return humanBet;
			
		case 1: //if no good match, return nothing (fold)
			return 0;
			
		return 0;
		}
}

Hand* ComputerPlayer::determineSwap(Hand* currentHand) //this function determines what cards the computer will swap
{
int handScore = currentHand.scoreHand(); //score of current hand
Hand* cardsToSwap = new Hand(); //array to be returned that holds cards that need to get swapped
Card* pairCard1 = currentHand[0]; //first card in the hand
Card* pairCard2 = currentHand[4]; //last card in the hand
	switch(handScore)
	{
		case 10: //no need to swap, awesome hand
			return 0;
		case 9: //no need to swap, awesome hand
			return 0;
		case 8: //no need to swap, awesome hand
			return 0;
		case 7: //no need to swap, awesome hand
			return 0;
		case 6: //no need to swap, awesome hand
			return 0;
		case 5: //no need to swap, awesome hand
			return 0;
		case 4: //checks which 2 cards are not part of 3 of a kind, sends those to get swapped
			for(int i=1; i<5; i++)
			{
				if(pairCard1.getNumber()==currentHand[i].getNumber())
					for(int j=1; j<5; j++)
						if(pairCard1.getNumber()!=currentHand[j].getNumber())
							cardsToSwap.addCard(currentHand[j]);
			}
			return cardsToSwap;
		case 3: //checks which card is not part of either of the two pairs, send it to get swapped
			int a = currentHand[0].getNumber();
			int b = currentHand[1].getNumber();
			int c = currentHand[2].getNumber();
			int d = currentHand[3].getNumber();
			int e = currentHand[4].getNumber();
			if(a!=(b|c|d|e))
				cardsToSwap.addCard(currentHand[0]);
			else if(b!=(a|c|d|e))
				cardsToSwap.addCard(crrentHand[1]);
			else if(c!=(a|b|d|e))
				cardsToSwap.addCard(currentHand[2]);
			else if(d!=(a|b|c|e))
				cardsToSwap.addCard(currentHand[3]);
			else
				cardsToSwap.addCard(currentHand[4]);
			return cardsToSwap;
		case 2: //checks which cards aren't part of a pair, sends them to get swapped
			for(int i=1; i<5; i++)
			{
				if(pairCard1.getNumber()==currentHand[i].getNumber())
					for(int j=1; j<5; j++)
						if(pairCard1.getNumber()!=currentHand[j].getNumber())
							cardsToSwap.addCard(currentHand[j]);
			}
			return cardsToSwap;

		for(int i=1; i<5; i++) //swaps all cards that are lower than a jack, but only the first 3 it finds
		{						//this allows the computer's hand to not seem too weak
			int count = 0;
			if(currentHand[i].getNumber()<11)
			{
				cardsToSwap.addCard(currentHand[i]);
				count++;
				if(count==3)
					break;
			}
		}
		return cardsToSwap;	
	}	
}
 */

