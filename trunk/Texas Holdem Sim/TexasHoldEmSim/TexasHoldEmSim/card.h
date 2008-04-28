// card.h

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using namespace std;
enum { HOLECARDS, FLOP, TURN, RIVER };
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
		friend bool operator== (card &card1, card &card2);
		friend ostream& operator<< (ostream& output, card &printCard);
		
    private:
        char suit;
        char num;
};

#endif
