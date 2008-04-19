// game.cpp

#include "game.h"

using namespace std;

/* MJB: game is basically the table/dealer in our simulation. It sets up 
        the number of players, initial chip count, odds for hole cards, etc.
   
   FIXME: THIS IS SEVERELY BROKEN BECAUSE IT RELIES A LOT ON HUMAN PLAYERS     
*/

game::game(GameFlow* gf): potSize(0), currentBet(0), numPlayers(0), handsPlayed(0), dealerNum(1), activePlayer(1), numCardsDealt(0), flow(gf)
{
	genTable();
} // game()

// MJB: Called to start a game
//      The constructor values are gotten from the configuration file
//stacks is gay...take it away.
void game::init(int num, int dealerNumber)
{
	numOfPlayers = num;

	for(int i=0; i<numOfPlayers; i++)
	{
		cPlayers.addChips(15);
		//not sure yet below
		cPlayers.pointToTable(&odds);
	}
	
	// MJB: WTF is this doing?
	//cPlayer.pointToOpponents(opps);

	hole.clear();
	hole.resize(0);
	potSize = 0;
	currentBet = 0;
	dealerNum = dealerNumber - 1;
	activePlayer = 1;
	numCardsDealt = 0;
	handsPlayed = 0;

	newHand();
} // init()

double game::stackSize(int n)
{
	if(n == 0)
		return cPlayer.stackSize();
	else
		return humans[n - 1].stackSize();
} // stackSize()

void game::betRaise(double amnt)
{
	cPlayers[activePlayer - 1].betRaise(amnt);

	////potSize += currentBet;
	potSize += amnt;

	activePlayer = (activePlayer + 1) % numOfPlayers;
	while(flow->isFolded(activePlayer))
	{
		activePlayer = (activePlayer + 1) % numOfPlayers;
	}
} // betRaise()

void game::callCheck(double amnt)
{
	cPlayers[activePlayer - 1].checkCall(amnt);

	////potSize += currentBet;
	potSize += amnt;

	activePlayer = (activePlayer + 1) % numOfPlayers;
	while(flow->isFolded(activePlayer))
	{
		activePlayer = (activePlayer + 1) % numOfPlayers;
	}
} // callCheck()

void game::fold()
{
	cPlayers[activePlayer - 1].fold();
	
	if(flow->roundNum == 1)
	{
		humans[activePlayer - 1].foldBeforeFlop();
	}

	activePlayer = (activePlayer + 1) % numOfPlayers;
	
	while(flow->isFolded(activePlayer ))
	{
		activePlayer = (activePlayer + 1) % numOfPlayers;
	} 

} // fold()

// MJB: Starts off a new hand.
// Puts everyone back in, moves blinds and dealer chip
// and sets who bets first.
void game::newHand()
{
	int b1, b2;

	handsPlayed++;
	hole.clear();
	hole.resize(0);
	
	for(int i=0; i<numOfPlayers; ++i)
	{
		cPlayers[i].clearCards();
		cPlayers[i].unfold();
		cPlayers[i].addFlopSeen();
	}
	
	dealerNum++;
	
	if(dealerNum == numOfPlayers)
		dealerNum = 0;

	b1 = (dealerNum+1) % numOfPlayers;
	b2 = (dealerNum+2) % numOfPlayers;

	// small blind
	cPlayers[b1].betRaise(.5);

	flow->player[b1].second = .5;

	// big blind
	cPlayers[b2].betRaise(1);

	flow->player[b2].second = 1.0;

	potSize = 1.5;
	////currentBet = 1;

	// next player is active
	activePlayer = (b2 + 1) % numOfPlayers;
}  // newHand()

void game::dealCards()
{
	numCardsDealt++;
	card card1(val[0], val[1]);
	cPlayer.addCard(card1);
	activePlayer = dealerNum + 1;
} // dealCard()

void game::pickWinner(int n)
{
	cPlayers[n-1].wonHand(potSize);
}  // pickWinner()

void game::addHole(string c)
{
	card card1(c[0], c[1]);
	hole.push_back(card1);
	if(hole.size() == 2)
	{
		cPlayer.setHoleCards(hole[0], hole[1]);
	}
} // addHole()

enum actionNames game::think()
{
	cPlayer.setDealer(dealerNum);
	
	int seatNum = (numPlayers - dealerNum) - 2;
	
	if(seatNum <= 0)
	{
		seatNum += numPlayers;
	}

	cPlayer.setSeatNumber(seatNum);

	return cPlayer.makeDec();
	// output to simulation box?
} // think()

void game::genTable()
{
	ifstream file;
	file.open("odds.txt");
	string hole, tmp;
	double weight;
	string a, b;

	odds.clear();
	
	for (int i = 0; i < 169; i++)
	{
		file >> hole;
		file >> weight;
		weight = weight / 31.5;

		a = hole[0];
		b = hole[1];

		if( hole.length() == 2 )
		{
			tmp = a + 'h' + b + 'c';
			odds[tmp] = weight;
			tmp = a + 'h' + b + 's';
			odds[tmp] = weight;
			tmp = a + 'h' + b + 'd';
			odds[tmp] = weight;

			tmp = a + 'c' + b + 'h';
			odds[tmp] = weight;
			tmp = a + 'c' + b + 's';
			odds[tmp] = weight;
			tmp = a + 'c' + b + 'd';
			odds[tmp] = weight;

			tmp = a + 's' + b + 'h';
			odds[tmp] = weight;
			tmp = a + 's' + b + 'c';
			odds[tmp] = weight;
			tmp = a + 's' + b + 'd';
			odds[tmp] = weight;

			tmp = a + 'd' + b + 'h';
			odds[tmp] = weight;
			tmp = a + 'd' + b + 'c';
			odds[tmp] = weight;
			tmp = a + 'd' + b + 's';
			odds[tmp] = weight;

		}
		else
		{ // hole.length() == 3
			tmp = a + 'h' + b + 'h';
			odds[tmp] = weight;
			tmp = a + 'c' + b + 'c';
			odds[tmp] = weight;
			tmp = a + 's' + b + 's';
			odds[tmp] = weight;
			tmp = a + 'd' + b + 'd';
			odds[tmp] = weight;
		}
	}
	
	file.close();

    // MJB: What does this print statement do?
	//cerr << "human weight table size = " << odds.size() << endl;
} // genTable()
