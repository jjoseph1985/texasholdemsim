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
	    Table(double m, int num);    
        
		void Init();
    	void InitPositions();
		void OddsTable(); 
		void NewRound();
		void DealCards(int whatRound);
		void NextAction();
		void DetDealer();
	    void DeclareWinner(int winner);
		bool Eligible();
		void CheckTime();

		Deck deck1;

    private:
	    bool limitAction, didAllIn;
	    double pot;
		int dealerPosition, numPlayers;
	    enum typeOfDeal{ HOLECARDS, FLOP, TURN, RIVER };
		enum posAtTable{ DEALER, SMALLBLIND, BIGBLIND, EARLY, MIDDLE, LATE };
		map<string, double> odds;
		vector<Player> playerList;
}; // Table

#endif
