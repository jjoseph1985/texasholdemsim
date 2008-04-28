// card.h

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using namespace std;
extern ofstream& simOut;

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
	
		// NE: overload equals comparison to see if two card are equal
		friend bool operator== (card& c1, card& c2);
		friend ostream& operator<< (ostream& output, card &printCard);
		friend bool operator> (card& c1, card& c2);
		friend bool operator< (card& c1, card& c2);
		
    private:
        char suit;
        char num;
};

#endif
