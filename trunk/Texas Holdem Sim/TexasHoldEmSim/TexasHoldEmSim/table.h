// table.h

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>

#include "card.h"
#include "hand.h"
#include "player.h"
#include "deck.h"

using namespace std;

class Table
{
    public:
	    Table();    

        Deck deck1;
		void Init();
    	enum posType setPos(int numPlayers);
		void OddsTable(); 
		void NewRound();
		void DealCard(enum round whatRound);
		void NextAction();
		void DetDealer();
	    void DeclareWinner(int winner);
		bool Eligible();
		void CheckTime();

    private:
	    bool limitAction;
	    double pot;
		int numPlayers, dealerPosition;
	    enum round { HOLECARDS, FLOP, TURN, RIVER };
		enum posAtTable{ DEALER, SMALLBLIND, BIGBLIND, EARLY, MIDDLE, LATE };
		map<string, double> odds;
		vector<Player> playerList;
}; // Table

#endif
