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
extern ofstream& simOut;

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
		double Call();
		double Fold();
		double Check();
		double Raise(double amnt);
		double AllIn();
		void   PreFlopDec(int n, bool limited);
		void   FoldHelper();
		void   BetHelper(bool limitAction);
		void   PostFlopDec(bool limitRaise);
        
        vector<card> holeCards;
        vector<card> tableCards;
        vector<card> allCards;
        
		// NE: evaluation cards
		Deck possibleTurnCards;
		Deck possibleRiverCards;

        hand myHand;
		map<string, double> preFlopOdds;
      
		double money;
		double myBet, dealHighBet;
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
