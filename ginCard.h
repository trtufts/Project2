//ginCard.h

#ifndef CARD_H
#define CARD_H

using namespace std;

class ginCard{
    public:
		 ginCard(int a, int b, int c, bool d);
		 ginCard();
		~ginCard();
    //private:
		int card;
		int value;
		int suit;
		bool deadwood;
		enum suits { NULLSUIT, SPADES, HEARTS, CLUBS, DIAMONDS };
};

#endif
