// table.h

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>

#include "card.h"
#include "hand.h"
#include "player.h"
using namespace std;

class Table
{
    public:
	    Table();    
        
		void Init();
    	enum posType setPos(int numPlayers);
		void OddsTable(); 
		void NewRound();
		void DealCard(round whatRound);
		void NextAction();
		void DetDealer();
	    void DeclareWinner(int winner);
		bool Eligible();
		void CheckTime();

    private:
	    bool limitAction;
	    double pot;
		int numPlayers, dealerPosition;
	    enum round { holecards, flop, turn, river };
		enum posAtTable{ dealer, small blind, big blind, early, middle, late };
		map<string, double> odds;
        vector<card> deck;
		vector<player> playerList;
}; // Table

#endif
