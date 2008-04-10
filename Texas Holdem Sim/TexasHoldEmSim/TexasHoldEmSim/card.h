//Deep Gold
//October 10, 2004
//card.h
//the underlying card class
//coded by Daniel Mack

#ifndef _CARD_H
#define _CARD_H

#include <string>
#include <iostream>

using namespace std;

class card
{
    public :
    
      card() : num('-'), suit('~') {};

        card(char n, char s):num(n),suit(s){}
    
        string whatcard() const
        {
            string temp;
            temp = temp + num;
            temp = temp + suit;
            return temp;
        }
    
	void setVal( char n, char s ) {
	  num = n;
	  suit = s;
	}
    
        void setnum(char n)
        {
            num = n;
        }

        void setsuit(char s)
        {
            suit = s;
        }    

        char getsuit() const
        {
            return suit;
        }           
 
        char getnum() const
        {
            return num;
        }
	
	  int getnum2() const
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
	   }
		     
    
    private :
        char suit, num;


};

#endif
