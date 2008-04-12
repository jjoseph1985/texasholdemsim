// card.h

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using namespace std;

class card
{
    public:
        card();
        card(char n, char s);
        string whatcard() const;
        void setVal(char n, char s);
        void setnum(char n);
        void setsuit(char s);
        char getsuit() const;
        char getnum() const;
        int  getfacenum() const;
    
    private:
        char suit;
        char num;
};

#endif
