#ifndef CARD_H
#define CARD_H


#include <iostream>
#include <string>
using namespace std;

class Card
{
	public:
		
		enum suit{spades, hearts, diamonds, clubs};
		Card();
		Card(int rank, Suit s);
		string toString()              const;  // return string version
        bool SameSuitAs(const Card& c) const;  // true if suit same as c
        int  GetRank()                 const;  // return rank, 1..13
        string suitString(Suit s)      const;  // return "spades", "hearts",...

	private:

	    string rankString(int r)       const;  // return "ace", "two", ...
	
		int myRank;
		Suit mySuit;

};

ostream& operator << (ostream& out, const Card& c);
bool operator == (const Card& lhs, const Card& rhs);
    


#endif