// game.h

#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include <string>
#include <map>
#include "comp.h"
#include "Round.h"
//#include "human.h"

using namespace std;

class game {
 public:
 	// new game constructor
  game( struct GameFlow* );
  	// called on each new hand
  void init( int, const vector<int>& , int dealerNumber);
  	// update the dealer number
  void setDealerNum( int n ) { dealerNum = n; }; 
  int getDealerNum() { return dealerNum; };
  int getActivePlayer() { return activePlayer; };
  void setActivePlayer(int p) {activePlayer = p; };
  	// get amount that one player holds in his stack
  double stackSize( int n );
  	// player raises an amount
  void betRaise( double );
  	// player calls, and places an amount in the pot
  void callCheck( double );
  	// active player folds
  void fold();
  void newHand();
  	// n indexes player
  bool isFolded( int n ) { return humans[n-1].checkFold(); };
  bool isBusted( int n ) { return humans[n-1].checkBust(); };
  double getPotSize() { return potSize; };
  	// alert game object of new card dealt
  void dealCard( string );  // queen of hearts == Qh, seven of diamonds == 7d
  	// alert game object of the winner
  void pickWinner( int n );
  	// alert game object of "me"'s hole cards
  void addHole( string );
  	// actions that think can recommend (fold, raise, check..)
  enum actionNames think();
  double getCurrBet() { return currentBet; };
  void resetCurrBet() { currentBet = 0; };

 private:
  void genTable();

  vector<humanPlayer > humans;
  compPlayer teddyKGB;
  vector<card> hole;
  map<string,double > odds;

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
