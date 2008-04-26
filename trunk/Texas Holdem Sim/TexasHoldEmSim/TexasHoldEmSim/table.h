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

enum typeOfDeal{ HOLECARDS, FLOP, TURN, RIVER };
enum posAtTable{ DEALER, SMALLBLIND, BIGBLIND, EARLY, MIDDLE, LATE };

class Table
{
    public:
	    Table(double m, int num);    
        
		void Init();
    	void InitPositions();
		void OddsTable(int numPlayers); 
		void NewRound();
		void DealCards(typeOfDeal d);
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
		map<string, double> preFlopOdds;
		vector<Player> playerList;
		vector<Player>::iterator iter;
}; // Table

#endif
