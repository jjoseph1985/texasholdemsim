// card.cpp

#include "card.h"
    
card::card(): num('-'), suit('~')
{

} // card()

card::card(char n, char s):num(n),suit(s)
{

} // card()

string card::whatcard() const
{
    string temp;
    temp = temp + num;
    temp = temp + suit;
    
    return temp;
} // whatcard()

void card::setVal( char n, char s )
{
    setnum(n);
    setsuit(s);
}  // setVal()

void card::setnum(char n)
{
    num = n;
} // setnum()

void card::setsuit(char s)
{
    suit = s;
} // setsuit()

char card::getsuit() const
{
    return suit;
} // getsuit()         


//returns name of card, ie. returns 'A' for ace, or '1' for one.
char card::getnum() const
{
    return num;
} // getnum()

//returns value of card, ie 14 for ace
int card::getfacenum() const
{
    int temp;
    
    if (num != 'T' && num != 'J' && num != 'Q' && num != 'K' && num != 'A')
    {
	    return num-'1';
    }

    switch(num)
    {
	    case 'T':
	    {
		    temp  = 10;
		    break;
	    }
	    case 'J':
	    {
		    temp = 11;
		    break;
	    }
	    case 'Q':
	    {
		    temp = 12;
		    break;
	    }
	    case 'K':
	    {
		    temp = 13;
		    break;
	    }
	    case 'A':
	    {
		    temp = 14;
		    break;
	    }
    }
    
    return temp;
} // getfacenum()