// game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "comp.h"
#include "round.h"

using namespace std;

class game
{
	public:
	    // MJB: Default constructor initializes the data members to default values and 
	    //      also generates the table of weights for hole card possibilities
	    game(GameFlow*);

	    // MJB: Called on each new hand. Initializer for a game class instance that takes arguments num
	    //      to set the number of players in the game, stacks to set the chip count for each player,
	    //      and dealerNumber to set the initial dealer
	    void init(int numPlayers, int startMoney, int dealerNumber);

	    // MJB: Dealer mutator/inspector
	    void setDealerNum(int index){ dealerNum = index; }; 
	    int  getDealerNum(){ return dealerNum; };
	    
	    // MJB: player mutator/inspector
	    int  getActivePlayer(){ return activePlayer; };
	    void setActivePlayer(int p){activePlayer = p; };

	    // MJB: Return the amount of chips that a player has.
	    double stackSize(int n);

	    // player raises an amount
	    void betRaise(double);

	    // MJB: Takes an amount and call/checks for that active player placing that money in the pot.
	    //      Moves the active player to the next eligible player.
	    void callCheck(double amnt);

	    // MJB: Folds the active player and increment to the next eligible player
	    void fold();


	    // MJB: Completes all necessary logic to initialize the game for a new hand. 
	    //      i.e., The dealer is incremented to the next player,
	    //            the blind positions are set,
	    //            the ante is forced,
	    //            the potSize is updated
	    //            the active players are updated
	    void newHand();
	    
	    // MJB: Check if a player has folded. (Used in determining 'active' players)
	    bool isFolded(int index);
	    
	    // MJB: This is never used anywhere, but it should return whether a player is
	    //      out of the game
	    bool isBusted(int index);
	    
	    // MJB: Returns the current potsize
	    double getPotSize();

	    // alert game object of new card dealt
	    void dealCard(string);  // queen of hearts == Qh, seven of diamonds == 7d

	    // MJB: declare winner based on passed in player number
	    void pickWinner(int n);

	    // MJB: takes string, parses it to create a card, and pushes it onto the hole vector. 
	    //      If hole is size 2, then it sets the hole cards for the computer.
	    void addHole(string);

	    // MJB: processes all knowledge of the current game state and proceeds to simulate 
	    //      and return a recommendation: fold, raise, check, call
	    enum actionNames think();
	    
	    
	    double getCurrBet();
	    void resetCurrBet();

	private:
	
	    // MJB: Read from text file the weights of all hole card combinations and place information into a map
	    void genTable();
        void activePlayerUpdate();

	    //vector<humanPlayer> humans;
	    vector<compPlayer> cPlayer;
	    vector<card> hole;
	    map<string, double> odds;

	    double potSize;
	    double currentBet; // do we need this here anymore?
	    int numPlayers;
	    int dealerNum;
	    int activePlayer;
	    int numCardsDealt;
	    int handsPlayed;
	    GameFlow* flow;
};

#endif