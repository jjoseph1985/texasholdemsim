// table.h

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <iostream>
#include <map>
#include <string>


#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"
#include "StringTokenizer.h"

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
		void ChangeBlinds();
		void EndGame();
		void GetHighBet();
		bool CheckAllBets(double HighBet);

		Deck deck1;

    private:
        void AddToMap(string cardStr, double weight);
        void DealCardHelper();
		void NextActionHelper(double HighBet, bool isHole);
        
	    bool limitRaise1; //limit because someone went all in
		bool limitRaise2; //limit because 2 raises have been made
		int numRaises;

	    double pot, bigBlind, smallBlind, highBet;
		int dealerPosition, numPlayers, numOfRoundsPlayed, winner;
		map<string, double> preFlopOdds;
		vector<Player> playerList;
		vector<Player> tempList10Players;
		vector<Player>::iterator iter;
}; // Table

#endif
