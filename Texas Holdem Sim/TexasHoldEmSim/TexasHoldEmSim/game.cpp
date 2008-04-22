// game.cpp

#include "game.h"

using namespace std;

/* MJB: game is basically the table/dealer in our simulation. It sets up 
        the number of players, initial chip count, odds for hole cards, etc.
   
   Removed all the human Player stuff;
*/

game::game(GameFlow* gf): potSize(0), currentBet(0), numPlayers(0), handsPlayed(0), dealerNum(1), activePlayer(1), numCardsDealt(0), flow(gf)
{
	genTable();
} // game()

// MJB: Called to start a game
//      The constructor values are gotten from the configuration file
void game::init(int numPlayers, int startMoney, int dealerNumber)
{
	this->numPlayers = numPlayers;

    for(int i=0; i < numPlayers; i++)
    {
        //cPlayers.addChips(startMoney);
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
    // activePlayer instead of n?
    return cPlayer[n-1].stackSize();

/*    
	if(n == 0)
		return cPlayer.stackSize();
	else
		return humans[n - 1].stackSize();
*/
} // stackSize()

void game::betRaise(double amnt)
{
	// depending on round, need to increment this again
	////currentBet++;

	cPlayer[activePlayer - 1].betRaise(amnt);


	////potSize += currentBet;
	potSize += amnt;

	ActivePlayerUpdate();
	
	while(flow->isFolded(activePlayer))
	{
		ActivePlayerUpdate();
	}
} // betRaise()

void game::callCheck(double amnt)
{

	cPlayer[activePlayer - 1].checkCall(amnt);

	////potSize += currentBet;
	potSize += amnt;

	ActivePlayerUpdate();
	
	while(flow->isFolded(activePlayer))
	{
		ActivePlayerUpdate();
	}
} // callCheck()

void game::fold()
{
	cPlayer[activePlayer - 1].fold();
		
	ActivePlayerUpdate();
	
	while(flow->isFolded(activePlayer ))
	{
		ActivePlayerUpdate();
	} 

} // fold()

void game::ActivePlayerUpdate()
{
    activePlayer = (activePlayer + 1) % numPlayers;
} // ActivePlayerUpdate

// MJB: Starts off a new hand.
// Puts everyone back in, moves blinds and dealer chip
// and sets who bets first.
void game::newHand()
{
	int b1;
	int b2;

	handsPlayed++;
	hole.clear();
	hole.resize(0);
	
	for(int i=0; i<numPlayers; ++i)
	{
	    cPlayer[i].clearCards();
		cPlayer[i].unfold();
	}
	
	dealerNum++;
	
	if(dealerNum == numPlayers)
		dealerNum = 0;

	b1 = (dealerNum+1) % numPlayers;
	b2 = (dealerNum+2) % numPlayers;

	// Force bet small blinds
	cPlayer[b1].betRaise(.5);
	flow->player[b1].second = .5;
    
    // Force bet big blinds
    cPlayer[b2].betRaise(1.0);
	flow->player[b2].second = 1.0;

	potSize = 1.5;
	////currentBet = 1;

	activePlayer = (b2 + 1) % numPlayers;
}  // newHand()

void game::dealCard(string val)
{
	numCardsDealt++;
	card card1(val[0], val[1]);
	cPlayer[activePlayer].addCard(card1);
	activePlayer = dealerNum + 1;
} // dealCard()

void game::pickWinner(int n)
{
    cPlayer[n].wonHand(potSize);
}  // pickWinner()

void game::addHole(string c)
{
	card card1(c[0], c[1]);
	hole.push_back(card1);
	
	if(hole.size() == 2)
	{
		cPlayer[activePlayer].setHoleCards(hole[0], hole[1]);
	}
} // addHole()

enum actionNames game::think()
{
	cPlayer[activePlayer].setDealer(dealerNum);
	
	int seatNum = (numPlayers - dealerNum) - 2;
	
	if(seatNum <= 0)
	{
		seatNum += numPlayers;
	}

	cPlayer[activePlayer].setSeatNumber(seatNum);

	return cPlayer[activePlayer].makeDec();
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

    // http://www.westonpoker.com/pokerInfo/preFlopOdds.php
	
	for (int i = 0; i < 169; i++)
	{
		file >> hole;
		file >> weight;
		weight = weight / 31.5;

		a = hole[0];		
		b = hole[1];
		
		cout << "\nhole[0]: " << a << "\nhole[1]: b " << b;

		if( hole.length() == 2 )
		{
			tmp = a + 'h' + b + 'c';
			odds[tmp] = weight;
			cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'h' + b + 's';
			odds[tmp] = weight;
			cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'h' + b + 'd';
			odds[tmp] = weight;    
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'c' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";			
			
			tmp = a + 'c' + b + 's';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";			
			
			tmp = a + 'c' + b + 'd';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 's' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 's' + b + 'c';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 's' + b + 'd';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'd' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'd' + b + 'c';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
			
			tmp = a + 'd' + b + 's';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";
		}
		else
		{ // suited cards
			tmp = a + 'h' + b + 'h';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'c' + b + 'c';
			odds[tmp] = weight;
			cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 's' + b + 's';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";

			tmp = a + 'd' + b + 'd';
			odds[tmp] = weight;
            cout << "\nodds[ " << tmp << "] = " << weight << "\n";			
		}
	}
	
	file.close();

    // MJB: What does this print statement do?
	//cerr << "human weight table size = " << odds.size() << endl;
} // genTable()

bool game::isFolded(int index)
{
    return cPlayer[index-1].checkFold();
}

bool game::isBusted(int index)
{
    return cPlayer[index-1].checkBust();
}	    

double game::getPotSize()
{
    return potSize;
}
double game::getCurrBet()
{
    return currentBet;
}

void game::resetCurrBet()
{
    currentBet = 0; 
}
