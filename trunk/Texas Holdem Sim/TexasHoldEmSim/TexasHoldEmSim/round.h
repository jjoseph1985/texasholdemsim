// round.h

#ifndef ROUND_H
#define ROUND_H

#include <vector>
#include <iostream>

using namespace std;

class GameFlow
{
    public:
        GameFlow();
        void init(int numPlayers);
        double currentBet();
        void fold(int index);
        double callCheck(int playNum);
        double raise(int playNum);
        bool isFolded(int playNum);
        bool newRound(int playNum);
    
	//MJB: private perhaps?
	    std::vector<std::pair<bool, double> > player;
	    int roundNum;		
	    int raiseCount;		// 2 raises per round max, high limit last 2 rounds
	    int playersLeft; 	// decreases as players fold
};

#endif
