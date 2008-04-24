// game.cpp

#include "comp.h"
#include "game.h"

using namespace std;

/* MJB: game is basically the table/dealer in our simulation. It sets up 
        the number of players, initial chip count, odds for hole cards, etc.
   
   Removed all the human Player stuff
   Changed some function names
*/

/*-------------------------------------*/

game::game(GameFlow* gf): potSize(0), currentBet(0), numOfPlayers(0), handsPlayed(0), dealerNum(1), activePlayer(1), flow(gf)
{
	genTable();
} // game()

/*-------------------------------------*/

// MJB: Called to start a game
// The constructor values are gotten from the configuration file
void game::init(int numOfPlayers, int startMoney, int dealerNumber)
{
	this->numOfPlayers = numOfPlayers;

    for(int i=0; i < numOfPlayers; i++)
    {
		// NE: give all players their initial money amount
        cPlayers[i].addMoney(startMoney);
    }	

	// MJB: WTF is this doing?
	// NE: I have no freakin clue!?!?
	// cPlayers.pointToOpponents(opps);

	hole.clear();
	hole.resize(0);
	potSize = 0;
	currentBet = 0;
	dealerNum = dealerNumber - 1;
	activePlayer = 1;
	handsPlayed = 0;

	newHand();
} // init()

/*-------------------------------------*/

double game::getMoney(int n)
{
    // MJB: activePlayer instead of n?
    return cPlayers[n-1].getMoney();

    // MJB: getMoney returns the current amount of $$$ a cPlayer has.
	/*	// NE: don't know what getMoney is???
		if(n == 0)
			return cPlayers.getMoney();
		else
			return humans[n - 1].getMoney();
	*/
} // getMoney()

/*-------------------------------------*/

void game::betRaise(double amnt)
{
	// depending on round, need to increment this again
	////currentBet++;

	cPlayers[activePlayer - 1].betRaise(amnt);

	potSize += currentBet;	// NE: adds what they owe
	potSize += amnt;		// NE: adds what their raise is

	activePlayerUpdate();

} // betRaise()

/*-------------------------------------*/

void game::callCheck(double amnt)
{

	cPlayers[activePlayer - 1].checkCall(amnt);

	potSize += currentBet;	// NE: adds what they owe
	potSize += amnt;		// NE: adds 

	activePlayerUpdate();
	
} // callCheck()

/*-------------------------------------*/

void game::fold()
{
	cPlayers[activePlayer - 1].fold();
		
	activePlayerUpdate();

} // fold()

/*-------------------------------------*/

void game::activePlayerUpdate()
{
    activePlayer = (activePlayer + 1) % numOfPlayers;
	
	// NE: continue until person that hasn't folded is selected
	while(flow->isFolded(activePlayer))
	{
		activePlayer = (activePlayer + 1) % numOfPlayers;
	}
} // activePlayerUpdate

/*-------------------------------------*/

// MJB: Starts off a new hand.
// Puts everyone back in, moves blinds and dealer chip
// and sets who bets first.
void game::newHand()
{
	int smallBlind;
	int bigBlind;

	handsPlayed++;
	hole.clear();
	hole.resize(0);
	
	for(int i=0; i<numOfPlayers; ++i)
	{
	    cPlayers[i].clearCards();
		cPlayers[i].unfold();
	}
	
	dealerNum++;
	
	if(dealerNum == numOfPlayers)
		dealerNum = 0;

	smallBlind = (dealerNum+1) % numOfPlayers;
	bigBlind = (dealerNum+2) % numOfPlayers;

	// Force bet small blinds
	cPlayers[smallBlind].betRaise(.5);
	flow->player[smallBlind].second = .5;
    
    // Force bet big blinds
    cPlayers[bigBlind].betRaise(1.0);
	flow->player[bigBlind].second = 1.0;

	potSize = 1.5;
	////currentBet = 1;

	activePlayer = (bigBlind + 1) % numOfPlayers;
}  // newHand()

/*-------------------------------------*/

void game::dealCards(string val)
{
	for(int i=0; i<numOfPlayers; i++)
	{
		//card dealtCard = theMainTable.getACard();
		//cPlayers[i].addCard(dealtCard);
	}
	for(int i=0; i<numOfPlayers; i++)
	{
		//card dealtCard = theMainTable.getACard();
		//cPlayers[i].addCard(dealtCard);
	}
	activePlayer = dealerNum + 1;
} // dealCard()

/*-------------------------------------*/

void game::givePotToWinner(int n)
{
    cPlayers[n].wonHand(potSize);
}  // pickWinner()

/*-------------------------------------*/

void game::addHole(string c)
{
	card card1(c[0], c[1]);
	hole.push_back(card1);
	
	if(hole.size() == 2)
	{
		cPlayers[activePlayer].setHoleCards(hole[0], hole[1]);
	}
} // addHole()

/*-------------------------------------*/

enum actionNames game::think()
{
	cPlayers[activePlayer].setDealer(dealerNum);
	
	int seatNum = (numOfPlayers - dealerNum) - 2;
	
	if(seatNum <= 0)
	{
		seatNum += numOfPlayers;
	}

	cPlayers[activePlayer].setSeatNumber(seatNum);

	return cPlayers[activePlayer].makeDec();
	// output to simulation box?
} // think()

/*-------------------------------------*/

// NE: this will genearte the table of odds
// MJB: Wondering, how I use this?
void game::genTable()
{
	ifstream file;
	file.open("odds.txt");
	string hole, tmp;
	double weight;
	string a, b;

	odds.clear();

    // http://www.westonpoker.com/pokerInfo/preFlopOdds.php
	// NE: this assumes there are 10 players...we will hard code that to make it easier...
	
	for (int i = 0; i < 169; i++)
	{
		file >> hole;
		file >> weight;
		weight = weight / 31.5;

		a = hole[0];		
		b = hole[1];
		
		cout << "\nhole[0]: " << a << "\nhole[1]: " << b;

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

/*-------------------------------------*/

bool game::isFolded(int index)
{
    return cPlayers[index-1].checkFold();
}

/*-------------------------------------*/

bool game::isBusted(int index)
{
    return cPlayers[index-1].checkBust();
}	    

/*-------------------------------------*/

double game::getPotSize()
{
    return potSize;
}

/*-------------------------------------*/

double game::getCurrBet()
{
    return currentBet;
}

/*-------------------------------------*/

void game::resetCurrBet()
{
    currentBet = 0; 
}
