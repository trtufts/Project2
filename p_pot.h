#ifndef PPOT_H
#define PPOT_H

class pot{
public:
    pot(double i);
    ~pot(void);
    void inputToPot(double i);
    double getPot(void);
    void resetPot();
private:
    double potTotal;
};
#endif

