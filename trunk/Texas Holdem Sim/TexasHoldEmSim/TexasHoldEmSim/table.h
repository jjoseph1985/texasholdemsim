// table.h

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>
#include <map>


#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"

using namespace std;

class Table
{
    public:
	    Table();    
        
		void Init();
    	void SetPos(int numPlayers);
		void OddsTable(); 
		void NewRound();
		void DealCard(int whatRound);
		void NextAction();
		void DetDealer();
	    void DeclareWinner(int winner);
		bool Eligible();
		void CheckTime();

		Deck deck1(vector<card> deck);

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
