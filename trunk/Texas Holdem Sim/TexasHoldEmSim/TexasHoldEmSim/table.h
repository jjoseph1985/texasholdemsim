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


enum { DEALER, SMALLBLIND, BIGBLIND, EARLY, MIDDLE, LATE };

class Table
{
    public:
	    Table(double m, int num, double sBAmnt);    
        
		void Init();
    	void InitPositions();
		void OddsTable(int numPlayers); 
		void NewRound();
		void DealCards(int type);
		void NextAction();
		void DetDealer();
	    void DeclareWinner(int winner);
		void Eligible();
		bool CheckTime();


		Deck deck1;

    private:
	    bool limitAction;
	    double pot, bigBlind, smallBlind;
		int dealerPosition, numPlayers;
		map<string, double> preFlopOdds;
		vector<Player> playerList;
		vector<Player> tempList10Players;
		vector<Player>::iterator iter;
}; // Table

#endif
