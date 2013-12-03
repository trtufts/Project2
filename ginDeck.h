//ginDeck.h
#ifndef DECK_H
#define DECK_H
#include "ginCard.h"


class ginDeck {
  public:
	ginDeck();
	void generateginDeck();
	void shuffleginCards(int q);
	ginCard drawCommunityginCard();
	ginCard drawStockginCard();
	void checkForEmptyStockPile();
	void discard(ginCard cardToDiscard);
	void showCommunityginCard();
	void showStockginCard();

  //private:
	ginCard communityArray[32];
	ginCard stockArray[52];
	ginCard *deckPointer;
	enum suits { NULLSUIT, SPADES, HEARTS, CLUBS, DIAMONDS };
};

#endif
