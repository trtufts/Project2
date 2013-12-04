#include "p_hand.h"
#include "p_card.h"
#include <iostream>
using namespace std;


hand::hand(void){};
hand::~hand(void){};

int hand::scoreHand(card *c){
    int lowest = getLowest(c);
    for(int i =1; i<5; i++)//for all suits
        if(hasRoyalFlush(c,i)) return 10;
    for(int i =1; i<5; i++)//for all suits
        if(hasStraightFlush(c,i,lowest)) return 9;
     for(int i =1; i<14; i++)//for all card numbers
        if(has4ofaKind(c,i)) return 8;
    if(hasFullHouse(c)) return 7;
    for(int i =1; i<5; i++)//for all suits
        if(hasFlush(c,i)) return 6;
    if(hasStraight(c,lowest)) return 5;
    for(int i =1; i<14; i++)//for all card numbers
        if(has3ofaKind(c,i)) return 4;
    if(has2Pair(c)) return 3;
    for(int i =1; i<14; i++)//for all card numbers
        if(hasPair(c,i)) return 2;
    return 1;
}


bool hand::hasCard(card *c, int s, int n){
    for(int i = 0; i<5; i++){
        if(c[i].getSuit()==s && c[i].getNumber()==n)    //iterates through the hand, tests if a card matches suit and number
            return true;
    }
    return false;
}

bool hand::hasNumCard(card *c, int n){
    for(int i = 0; i<5; i++){
        if(c[i].getNumber()==n)         //iterates through the hand, tests if a card matches number
            return true;
    }
    return false;
}

bool hand::hasRoyalFlush(card *c, int s){
    if(hasCard(c,s,10)&&hasCard(c,s,11)&&hasCard(c,s,12)&&hasCard(c,s,13)&&hasCard(c,s,1)) return true;//tests if the hand has the royal flush cards
        else return false;
}
bool hand::hasStraightFlush(card *c, int s, int l){
    if(l!=1){//if there is no ace
        if(hasCard(c,s,l)&&hasCard(c,s,l+1)&&hasCard(c,s,l+2)&&hasCard(c,s,l+3)&&hasCard(c,s,l+4)) return true;//returns if there is a sequence of cards, with no ace
            else return false;
    }
    else{       //if there is an ace, need to find lowest again
        int lowest=0;
        if(c[lowest].getNumber()==1) lowest++;//takes care of the case when ace is the first card
        for(int i = 1; i<5; i++){
        if((c[i].getNumber()<c[lowest].getNumber())&&c[i].getNumber()!=1){
            lowest=i;
        }
    }
        l = c[lowest].getNumber(); //get lowest value besides ace
        if(hasCard(c,s,l)&&hasCard(c,s,l+1)&&hasCard(c,s,l+2)&&hasCard(c,s,l+3)) return true;//returns if 4 cards are sequential, with an ace
            else return false;
    }
}
bool hand::has4ofaKind(card *c, int n){
    if(hasCard(c,1,n)&&hasCard(c,2,n)&&hasCard(c,3,n)&&hasCard(c,4,n)) return true;//tests if there is 4 of the same card
        else return false;
}
bool hand::hasFullHouse(card *c){
    int tripleNum;
    bool triple;
    for(int i =1; i<14; i++){
        if(has3ofaKind(c,i)){//first find the triple
            triple = true;
            tripleNum = i;   //mark down the number of the triple
            break;
        }
    }
    if(triple){               //if a triple was found, find a pair
        for(int i =1; i<14; i++){
            if(hasPair(c,i)&&i!=tripleNum) //find pair with different number than the triple
                return true;
        }
    }
    return false;
}
bool hand::hasFlush(card *c, int s){
    if(c[0].getSuit()==s && c[1].getSuit()==s && c[2].getSuit()==s && c[3].getSuit()==s && c[4].getSuit()==s) return true;
        else return false;
}
bool hand::hasStraight(card *c, int l){
    if(l!=1)//if there is no ace
    if(hasNumCard(c,l)&&hasNumCard(c,l+1)&&hasNumCard(c,l+2)&&hasNumCard(c,l+3)&&hasNumCard(c,l+4)) return true;
            else return false;
    else{       //if there is an ace, need to find lowest again
        int lowest=0;
        if(c[lowest].getNumber()==1) lowest++;//takes care of the case when ace is the first card
        for(int i = 1; i<5; i++){
        if((c[i].getNumber()<c[lowest].getNumber())&&c[i].getNumber()!=1){
            lowest=i;
        }
    }
        l = c[lowest].getNumber(); //get lowest value besides ace
        if(hasNumCard(c,l)&&hasNumCard(c,l+1)&&hasNumCard(c,l+2)&&hasNumCard(c,l+3)) return true;//if 4 cards are sequential
            else return false;
    }
}
bool hand::has3ofaKind(card *c, int n){
    int count = 0;
    for(int i = 0; i<5; i++)
            if(c[i].getNumber()==n)
                    count++;
    if(count==3)return true;
        else return false;
}
bool hand::has2Pair(card *c){
    int pair1num;
    bool pair1;
    for(int i =1; i<14; i++){
        if(hasPair(c,i)) { //find first pair
                pair1 = true;
                pair1num = i;
                break;
        }
    }
    if(pair1)
        for(int i =1; i<14; i++)
            if(hasPair(c,i)&&i!=pair1num) //find second pair, with different number
                return true;
    return false;
}

bool hand::hasPair(card *c, int n){
    int count = 0;
    for(int i = 0; i<5; i++)
            if(c[i].getNumber()==n)
                    count++;
    if(count==2)return true;
        else return false;
}
int hand::getHighest(card *c){
    int highest=0;
    for(int i = 0; i<5; i++){
        if(c[i].getNumber()==1) return 15; //if there is an ace, return 15, which is higher than a king and higher than a joker.
        if(c[i].getNumber()>c[highest].getNumber()){
            highest=i;
        }
    }
    return c[highest].getNumber();

        }

int hand::getLowest(card *c){
    int lowest=0;
    for(int i = 0; i<5; i++){
        if(c[i].getNumber()<c[lowest].getNumber()){
            lowest=i;
        }
    }
    return c[lowest].getNumber();
}

void hand::handDriver(){
    hand *test = new hand();
    card *cards = new card[5];
    /*********card(suit,number)******/
    cards[0] = card(1,10);
    cards[1] = card(1,11);
    cards[2] = card(1,12);
    cards[3] = card(1,13);
    cards[4] = card(1,1);
    cout<<"royal flush test should result 10, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(2,4);
    cards[1] = card(2,5);
    cards[2] = card(2,6);
    cards[3] = card(2,7);
    cards[4] = card(2,8);
    cout<<"straight flush test should result 9, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(1,4);
    cards[1] = card(2,4);
    cards[2] = card(3,4);
    cards[3] = card(4,4);
    cards[4] = card(2,8);
    cout<<"4 of a kind test should result 8, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(1,10);
    cards[1] = card(4,10);
    cards[2] = card(3,3);
    cards[3] = card(2,3);
    cards[4] = card(1,3);
    cout<<"full house test should result 7, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(2,4);
    cards[1] = card(2,11);
    cards[2] = card(2,6);
    cards[3] = card(2,7);
    cards[4] = card(2,12);
    cout<<"flush test should result 6, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(1,1);
    cards[1] = card(2,6);
    cards[2] = card(3,7);
    cards[3] = card(4,8);
    cards[4] = card(1,9);
    cout<<"straight test should result 5, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(1,1);
    cards[1] = card(2,6);
    cards[2] = card(3,2);
    cards[3] = card(4,2);
    cards[4] = card(1,2);
    cout<<"3 of a kind test should result 4, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(1,1);
    cards[1] = card(2,1);
    cards[2] = card(3,7);
    cards[3] = card(4,6);
    cards[4] = card(1,6);
    cout<<"2 pair test should result 3, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(1,1);
    cards[1] = card(2,1);
    cards[2] = card(3,7);
    cards[3] = card(4,8);
    cards[4] = card(1,9);
    cout<<"pair test should result 2, result: "<<test->scoreHand(cards)<<endl;
    cards[0] = card(1,1);
    cards[1] = card(2,3);
    cards[2] = card(3,5);
    cards[3] = card(4,7);
    cards[4] = card(1,9);
    cout<<"highcard test should result 1, result: "<<test->scoreHand(cards)<<" with high card 15, result: "<<getHighest(cards)<<endl;
    cards[0] = card(1,7);
    cards[1] = card(2,6);
    cards[2] = card(3,7);
    cards[3] = card(4,2);
    cards[4] = card(1,9);
    cout<<"get lowest card should result 2, result: "<<getLowest(cards)<<endl;
    cards[0] = card(1,7);
    cards[1] = card(2,6);
    cards[2] = card(1,1);
    cards[3] = card(4,2);
    cards[4] = card(1,9);
    cout<<"check if has ace of spades, result: "<<hasCard(cards,1,1)<<endl;
    cards[0] = card(1,7);
    cards[1] = card(2,6);
    cards[2] = card(1,1);
    cards[3] = card(4,2);
    cards[4] = card(1,9);
    cout<<"check if has a 7 card, result: "<<hasNumCard(cards,7)<<endl;
}
