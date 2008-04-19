// state.h

#ifndef STATE_H
#define STATE_H

#include <list>
#include <vector>
#include <iostream>

#include "holecards.h"
#include "card.h"
#include "hand.h"

using namespace std;

class seat
{
    public:
     holeCards cards;
        double amtBet;
        int    index;
}; // seat


class Table
{
    public:
	    Table( list<int>, double, double);
	    
	    // Copy Constructor
	    Table(Table &);
	    
	    // MJB: Informs state of the action taken
	    void   Fold();
	    void   Bet();
	    void   Call();
	    
	    // MJB: Winner winner chicken dinner. Return winnings if any
	    double amtWon();
	    
	    // MJB: Round mutator/inspector
	    int    getrnd() { return round; };
	    void   setRound( int r );
	    
	    // MJB: Return number of players (left?)
	    int    numberPlayers();
	    
	    // MJB: Returns index into player vector for that player
	    int    getIndex( int index);
	    
	    // Sets holecards for a player n
	    void   setHole( int n, holeCards );
	    
	    // Deals a card matching a string
        void   dealCard( string );
        
	    bool   isGameOver();

    private:
        // MJB: Moves to then next round of betting or ends the current hand
	    void   updateRound( bool );

        // MJB: Uses hand evaluation to determine the winner of a hand among remain players in state	    
	    void   pickWinner();

	    double currBet;
	    bool   gameOver;
        double winnings;
	    double pot;
	    double my_share;
	    int    round;
	    bool   compout; // MJB don't need this
        vector<card> table;
	    list<seat>   players;
	    list<seat>::iterator plturn;	//Turn designator for player
	    list<seat>::iterator lastRaiser;
}; // Table

#endif
