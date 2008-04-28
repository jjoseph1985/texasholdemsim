// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <vector>
#include <limits>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "card.h"
#include "hand.h"
#include "deck.h"

using namespace std;

class Player
{

  public:
        enum { DEALER=0, SMALLBLIND=1, BIGBLIND=2};
        
        Player();
        Player(double m, map<string, double>& preFlop, string name);
        
        void AddMoney(double amt);
		double GetMoney();
        
        hand ShowHand();
        void AddCard(card c, int loc);
        void ClearCards();
        
		double Action(bool limitRaise, double currentHighBet, bool amHole, bool amFirstIter);
        bool DidFold();
        bool DidBust();
        bool DidAllIn();
        bool DidRaised();
        void Reset();
        void ResetRaised();
		void ResetMyBet();
		void SetBusted();

		string GetName();
		double GetBet();

		void SetSB(double amnt);
		void SetBB(double amnt);
		
		int    GetJob();
		void   SetJob(int theJob);		

 
  private:
        void CombineCards();
		double Call(double theHighBet);
		double Fold();
		double Check();
		double Raise(double theHighBet, double amnt);
		double AllIn();
  
        vector<card> holeCards;
        vector<card> tableCards;
        vector<card> allCards;
        
		// NE: evaluation cards
		Deck possibleTurnCards;
		Deck possibleRiverCards;

        hand myHand;
		map<string, double> preFlopOdds;
      
		double money;
		double myBet;
		double smallBlind;
		double bigBlind;

		string name;

        bool fold;
        bool bust;
        bool allIn;
        bool raised;
        int  job;

     /* Unimplemented AI Stuff
        enum actionNames makeDec();     
        enum actionNames preflopDec();
        enum actionNames simulate();
        double sim( Table& );
        double trial( Table& );
        double amtBet;

        map<string, bool> aDeck;
        map<int, string>  bDeck;
     */
};

#endif
