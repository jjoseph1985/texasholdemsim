// game.h

#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include <string>
#include "comp.h"
#include "Round.h"
//#include "human.h"

using namespace std;

class game {
 public:
  game( struct GameFlow* );
  void init( int, const vector<int>& , int dealerNumber);
  void setDealerNum( int n ) { dealerNum = n; }; 
  int getDealerNum() { return dealerNum; };
  int getActivePlayer() { return activePlayer; };
  void setActivePlayer(int p) {activePlayer = p; };
  double stackSize( int n );
  void betRaise( double );
  void callCheck( double );
  void fold();
  void newHand();
  bool isFolded( int n ) { return humans[n-1]->checkFold(); };
  bool isBusted( int n ) { return humans[n-1]->checkBust(); };
  double getPotSize() { return potSize; };
  void dealCard( string );  // queen of hearts == Qh, seven of diamonds == 7d
  void pickWinner( int n );
  void addHole( string );
  enum actionNames think();
  double getCurrBet() { return currentBet; };
  void resetCurrBet() { currentBet = 0; };

 private:
  vector<humanPlayer* > humans;
  compPlayer teddyKGB;
  vector<card> hole;

  double potSize;
  double currentBet; // do we need this here anymore?
  int numPlayers;
  int dealerNum;
  int activePlayer;
  int numCardsDealt;
  int handsPlayed;
  struct GameFlow* flow;
};

#endif
