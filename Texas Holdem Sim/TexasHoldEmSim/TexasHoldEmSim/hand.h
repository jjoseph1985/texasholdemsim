// hand.h

#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>

#include "card.h"

using namespace std;

enum typeName { BLANK, JUNK, PAIR, TWOPAIR, THREEKIND, STRAIGHT, FLUSH, FULL, FOURKIND, SFLUSH, RFLUSH };

class handType
{
    public:
        handType();
        
        // MJB: Why isn't their just a setkicker method?
        void setType( enum typeName tn, int a = 0, int b = 0, int c = 0, int d = 0, int e = 0 );
        enum typeName getType() {return label;};         
        bool beats( handType& );
        bool ties( handType& );
        void clear();

    private:
        enum typeName label;
        int kick1;
        int kick2;
        int kick3;
        int kick4;
        int kick5;
}; // handType


class hand
{
    public:
        hand();
        
        // MJB: takes in five cards into a cards vector and sorts them by rank
        void init(const card&, const card&, const card&, const card&, const card&);
        
        // MJB: add card next to the hand in order
        void addCard(const card&);
        
        // MJB: return a type of hand in the form of a handType
        handType getType();
        
        // MJB: Clears cards, handType, and possHands vectors
        void clear();
        
        
        bool beats( hand& );
        bool ties( hand& ); // MJB: private maybe? beats() should probably call this

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

        vector<card> cards;  
        handType myType;
        vector< vector<card> > possHands; // a vector of all possible hands
        bool typeValid;  // ?
}; // hand

#endif
