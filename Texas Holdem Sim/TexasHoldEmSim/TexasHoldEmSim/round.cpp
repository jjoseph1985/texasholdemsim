// round.cpp

#include  "round.h"

// initialize with the number of players at the start of the game
void GameFlow::init(int numPlayers)
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
}  // init()

// least cumulative amount player must have in the pot to keep playing
double GameFlow::currentBet()
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
} currentBet()

// player folds
void GameFlow::fold(int index)
{
	player[index].first = false;
	playersLeft --;
} // fold()

// player calls / checks
double GameFlow::callCheck(int index)
{
	double putIntoPot = (currentBet() - player[index].second);
	player[index].second = currentBet();
	return putIntoPot;
} // callCheck()


// Player raise. returns the amount the player had just added into the pot
double GameFlow::raise(int index)
{
    double putIntoPot = (currentBet() - player[index].second) + 1.0;
	if( roundNum == 3 || roundNum == 4)
		putIntoPot++;
	
	player[index].second += putIntoPot; 
	raiseCount ++;
	return putIntoPot;
} // raise()

// player has folded
bool GameFlow::isFolded(int index)
{
	return ( ! player[index].first);
} // isFolded()

// returns whether it is time for a new round of betting
bool GameFlow::newRound(int index)
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
} // newRound()