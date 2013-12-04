#ifndef PCARD_H
#define PCARD_H
class card{

public:
    card(int s, int n);
    card(void);
    ~card(void);
    int getSuit() const;
    int getNumber() const;
    void setValues(int s, int n);
private:
    int suit,number;
};
#endif // CARD_H
