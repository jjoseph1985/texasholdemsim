// table.h

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>
#include <map>

#include "player.h"
#include "card.h"
#include "hand.h"
#include "deck.h"

using namespace std;

class Table
{
    public:
	    Table();    

        Deck deck1(vector<card> deck);
		void Init();
    	void setPos(int numPlayers);
		void OddsTable(); 
		void NewRound();
		void DealCard(int whatRound);
		void NextAction();
		void DetDealer();
	    void DeclareWinner(int winner);
		bool Eligible();
		void CheckTime();
		Player c;
        		

    private:
	    bool limitAction;
	    double pot;
		int numPlayers, dealerPosition;
	    enum round { HOLECARDS, FLOP, TURN, RIVER };
		enum posAtTable{ DEALER, SMALLBLIND, BIGBLIND, EARLY, MIDDLE, LATE };
		map<string, double> odds;
		//vector <Player> ct; // WTF I CAN MAKE ONE IN MAIN?????
}; // Table

#endif
