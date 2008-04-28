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
#include "shared.h"

using namespace std;

class Player
{

  public:
        Player();
        Player(double m, map<string, double>& preFlop, string name);
        
        void AddMoney(double amt);
		double GetMoney();
        
        hand GetHand();
		void MakeHand();
        void AddCard(card c, int loc);
        void ClearCards();
        
		double Action(bool limitRaise, double currentHighBet, bool amHole, bool amFirstIter, int numOfplay);
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
		void   SetSkillLvl();
        int    GetSkillLvl();
        void   SortHoleCards();
        void   SetPreFlopOdds(map<string, double>& oddTbl);

 
  private:
        void   CombineCards();
		double Call(double theHighBet);
		double Fold();
		double Check();
		double Raise(double theHighBet, double amnt);
		double AllIn();
		void   PreFlopDec(int n, bool limited, double high);
		void   FoldHelper(double currentHighBet);
		void   BetHelper(bool limitAction, double currentHighBet);
		void   PostFlopDec(bool limitRaise, double currHighBet);
        
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
        int  skillLvl;
        int  decision;
        int  raiseAmt;

     /* Unimplemented AI Stuff
        enum actionNames makeDec();     
        enum actionNames simulate();
        double sim( Table& );
        double trial( Table& );

        map<string, bool> aDeck;
        map<int, string>  bDeck;
     */
};

#endif
