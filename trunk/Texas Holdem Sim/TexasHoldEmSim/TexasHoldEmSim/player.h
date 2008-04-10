// computer.h
#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <map>
#include <vector>
#include "holecards.h"
#include "card.h"
#include "hand.h"
#include "state.h"

using namespace std;

enum actionNames {FOLD, RAISE, CHECK, BET, CALL};
enum posType {EARLY, MIDDLE, LATE, BLINDS}; //DUNNO!?!?!??

const int NUMTRIALS = 4;

class compPlayer {
	public:
		  compPlayer();
		  void pointToOpponents(vector<humanPlayer* >);
		  void addChips(int);
		  
		  double stackSize();
		  
		  void addCard(card);
		  void newHand();
		  
		  void setHoleCards(card, card);
		  void fold();
		  void betRaise(double);
		  void checkCall(double);
		  void busted();
		  void unfold();

		  bool checkBust();
		  bool checkFold();
		  void opponentBet();
		  void opponentRaised();
		  void setSeatNumber(int);
		  void setPotSize(double);
		  void wonHand(double);
		  void clearCards();
		  void setDealer(int) { dealerNum = n; };

		  enum actionNames makeDec();

	private:
		  enum actionNames preflopDec();
		  enum posType setPosition( const int& );
		  enum actionNames simulate();
		  double sim( State& );
		  double trial( State& );
		  void initTable( map<string,double>& );

		  map<string, double> weightTable;
		  holeCards myCards;
		  vector<humanPlayer* > opposition;
		  vector<card> tablecards;
		  hand myHand;
		  double chipCount;
		  int handsPlayed;
		  int flopsSeen;
		  bool out;
		  bool bust;		//run outta $$$
		  bool betPlaced;
		  bool raiseMade;
		  int posAtTable;
		  int dealerNum;
		  double potSize;

		  map<string, bool>  aDeck;
		  map<int, string> bDeck;
};

#endif
// computer.h