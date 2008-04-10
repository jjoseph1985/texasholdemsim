
#ifndef _STATE_H
#define _STATE_H


#include <list>
#include <vector>
#include "holecards.h"
#include "card.h"
#include "hand.h"

using namespace std;

class seat {
  public:
    double amtBet;
    holeCards cards;
    int index;
};


class State
{
    public:
	
	State( list<int>, double, double); //Constructor
	State(State &); 			// Copy Constructor	
	void Fold();
	void Bet();
	void Call();
	double gainloss();
	int getrnd() { return round; };
	void setRound( int r ) { round = r; };
	int numberPlayers() { return players.size(); };
	int getIndex( int );
	void setHole( int, holeCards );
    void dealCard( string );
	bool isGameOver() { return gameOver; };

    private:
	void updateRound( bool );
	void pickWinner();

	list<seat> players;
	double pot;
	double my_share;
        vector<card> table;
	int round;
	bool compout;
	list<seat>::iterator plturn;	//Turn designator for player
	list<seat>::iterator lastRaiser;
	double currBet;
	bool gameOver;
        double winnings;
};


#endif
