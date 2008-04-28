// hand.h

#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>
#include <iostream>

#include "card.h"
#include "handtype.h"

using namespace std;

class hand
{
    public:
        hand();
        
        // MJB: takes in seven cards into a cards vector and sorts them by rank
        void initHand(vector<card>& table, vector<card>& hole);
        
        // MJB: add card next to the hand in order
        /*void addCard(const card&);*/
        
        // MJB: return a type of hand in the form of a handType
        handType getType();
        
        // MJB: Clears cards, handType, and possHands vectors
        void clear();
        
        vector<card> cards;  

		friend bool operator> (hand& hand1, hand& hand2);
		friend bool operator== (hand& hand1, hand& hand2);
		friend ostream& operator<< (ostream& output, hand &printHand);

    private:
        // MJB: determine and return a handType
        handType typeOf( const vector<card>& );
        
        // MJB: This just adds 5 cards to a hand, it's mainly used when trying
        //      to find the best possible hand. (5 indeces are into a card vector)
        void addcombo( int, int, int, int, int );
        
        // MJB: Self explanatory
        bool isStraight( const vector<card>&, handType& );
        bool isFlush( const vector<card>&, handType& );
        bool is4kind( const vector<card>&, handType& );
        bool is3kind( const vector<card>&, handType& );
        bool isFull(  const vector<card>&, handType& );
        bool is2pair( const vector<card>&, handType& );
        bool isPair(  const vector<card>&, handType& );

        handType myType;
        vector< vector<card> > possHands; // a vector of all possible hands
        bool typeValid;  // ?
}; // hand

#endif
