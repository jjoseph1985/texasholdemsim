// state.h

#ifndef STATE_H
#define STATE_H

#include <list>
#include <vector>

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


class State
{
    public:
	    State( list<int>, double, double);
	    State(State &);  // Copy Constructor	
	    void   Fold();
	    void   Bet();
	    void   Call();
	    double winslosses();
	    int    getrnd() { return round; };
	    void   setRound( int r );
	    int    numberPlayers();
	    int    getIndex( int );
	    void   setHole( int, holeCards );
        void   dealCard( string );
	    bool   isGameOver();

    private:
	    void   updateRound( bool );
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
}; // State

#endif
