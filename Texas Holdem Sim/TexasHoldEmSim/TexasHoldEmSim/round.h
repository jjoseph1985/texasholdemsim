// round.h

#ifndef ROUND_H
#define ROUND_H

#include <vector>
#include <iostream>

using namespace std;

struct GameFlow
{
	// initialize with the number of players at the start of the game
	void init(int numPlayers)
	{
		player.clear();
		roundNum = 1;
		raiseCount = 0;
		playersLeft = numPlayers;
		
		for (int i = 0; i < numPlayers; i ++)
		{
			pair<bool, double> p(true, 0.0);
			player.push_back(p);
		}
	}
	
	// least cumulative amount player must have in the pot to keep playing
	double currentBet()
	{
		double current = 0.0;
		for (int i=0; i<player.size(); i++)
		{
			if (player[i].first == true && current < player[i].second)
			{
				current = player[i].second;
			}
		}
		return current;
	}
	
	// player folds
	void fold(int index)
	{
		player[index].first = false;
		playersLeft --;
	}
	
	// player calls / checks
	double callCheck(int index)
	{
		double putIntoPot = (currentBet() - player[index].second);
		player[index].second = currentBet();
		return putIntoPot;
	}
	
	// player raises
	// returns the amount the player had just added into the pot
	double raise(int index)
	{
	    double putIntoPot = (currentBet() - player[index].second) + 1.0;
		if( roundNum == 3 || roundNum == 4)
			putIntoPot++;
		player[index].second += putIntoPot; 
		raiseCount ++;
		return putIntoPot;
	}
	
	// player has folded
	bool isFolded(int index)
	{
		return ( ! player[index].first);
	}
	
	// returns whether it is time for a new round of betting
	bool newRound(int index)
	{
		double contribution = player[index].second; // current player's pot contribution amount
		// all pot contribution sizes must be equal for those still playing
		for (int i = 1; i < player.size(); i ++)
		{
			if (isFolded(i)) // ignore folded players
			{
				continue;
			}
			if (player[i].second != contribution)
			{
				return false;
			}
		}
		return true; // all players are set
	}
	
	// index: player number   bool: hasn't folded   int: amount put in pot so far
	std::vector<std::pair<bool, double> > player;
	int roundNum;		
	int raiseCount;		// 2 raises per round max, high limit last 2 rounds
	int playersLeft; 	// decreases as players fold
};



#endif
