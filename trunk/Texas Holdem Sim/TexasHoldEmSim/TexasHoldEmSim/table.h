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



class Table
{


    public:
        enum jobs { DEALER, SMALLBLIND, BIGBLIND};    
	    Table(double m, int num, double sBAmnt);    
        
		void Init();
    	void InitPositions();
    	void ChangePositions();
		void OddsTable(int numPlayers); 
		void NewRound();
		void DealCards(const int type);
		void NextAction();
	    void DeclareWinner();
		void Eligible();
		void ChangeBlinds();
		void EndGame();
		void GetHighBet();
		bool CheckAllBets(double highBet);

		Deck deck1;

    private:
        void AddToMap(string cardStr, double weight);
        void DealCardHelper(const int type);
		void NextActionHelper(double highBet, bool isHole);
		void FindJob(const int desiredJob);
        
	    bool limitRaise1; //limit because someone went all in
		bool limitRaise2; //limit because 2 raises have been made
		int numRaises;

	    double pot, bigBlind, smallBlind, highBet;
		int numPlayers, numOfRoundsPlayed, winner;
		map<string, double> preFlopOdds;
		vector<Player> playerList;
		vector<Player> tempList10Players;
		vector<Player>::iterator iter;
}; // Table

#endif
