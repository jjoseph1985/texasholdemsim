// computer.h

#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <map>
#include <vector>
#include "holecards.h"
#include "human.h"
#include "card.h"
#include "hand.h"
#include "state.h"

using namespace std;

enum actionNames { FOLD, RAISE, CHECK, BET, CALL };
enum posType { EARLY, MIDDLE, LATE, BLINDS };

const int NUMTRIALS = 4;

class compPlayer {
public:
  compPlayer();
  void pointToOpponents( vector<humanPlayer* > x ) { opposition = x; };
  void addChips(int);
  
  double stackSize();
  
  void addCard(card);
  void newHand();
  
  void setHoleCards(card, card);
  void fold();
  void betRaise( double );
  void checkCall( double );
  void busted();
  void unfold();
  bool checkBust();
  bool checkFold();
  void opponentBet() { betPlaced = true; };
  void opponentRaised() { raiseMade = true; };
  void setSeatNumber( int n ) { posAtTable = n; };
  void setPotSize( double x ) { potSize = x; };
  void wonHand( double n ) { chipCount += n; };
  void clearCards();
  void setDealer( int n ) { dealerNum = n; };

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
  bool bust;
  bool betPlaced;
  bool raiseMade;
  int posAtTable;
  int dealerNum;
  double potSize;

  map<string, bool>  aDeck;
  map<int, string> bDeck;
};


#endif

