// Player.cpp

#include "player.h"

using namespace std;

Player::Player()
{

}


Player::Player(double m,map<string, double>& preFlop, string Name): job(-1), fold(false), bust(false), allIn(false), myBet(0)
{ 
    money = m;
	preFlopOdds = preFlop;
	name = Name;
} // Player()

        
void Player::AddMoney(double amt)
{
    money += amt;
} // AddMoney()


double Player::GetMoney()
{
    return money;
} // GetMoney()


hand Player::ShowHand()
{
    return myHand;
} // ShowHand()


void Player::AddCard(card c, int loc)
{
    if(loc == HOLECARDS)
    {
        holeCards.push_back(c);   
    }
    else if( loc == FLOP || loc == TURN || loc == RIVER)
    {
        tableCards.push_back(c);
    }
   
} // AddCard()


void Player::ClearCards()
{
    myHand.clear();
    tableCards.clear();
    holeCards.clear();
	allCards.clear();
} // ClearCard()


double Player::Action(bool limitRaise, double currentHighBet, bool isHole, bool isFirstIter)
{
	possibleTurnCards.ShuffleCard();
	possibleRiverCards.ShuffleCard();
	
	if(job==SMALLBLIND && isFirstIter)
	{
	    money -= smallBlind;
	    return smallBlind;
	}
	else if(job==BIGBLIND && isFirstIter)
	{
	    money -= bigBlind;
	    return bigBlind;
	}
	

	/*---------AI STUFF TO BE REPLACED---------*/
	int decision = (rand()%4)+1; //1=check;2=call;3=raise&call;4=fold
	//cout << "D1:" << decision << " ";
	//Can't raise if limited and can't check if they owe money
	while((limitRaise && decision == 3) || (currentHighBet > myBet && decision == 1))
	{
		decision = (rand()%4)+1;
	}
	//cout << "D2:" << decision << "\n";
	/*---------DON'T REPLACE BELOW---------*/
	switch(decision)
	{//now do decision
		case 1 : 
			return Check();
			break;
		case 2 : 
			return Call(currentHighBet);
			break;
		case 3 : 
			return Raise(currentHighBet, 10);
			break;
		case 4 : 
			return Fold();
			break;
	    default:
	        return -1;
	}
} // Action()

bool Player::DidFold()
{
    return fold;
} // DidFold()


bool Player::DidBust()
{
    return bust;
} // DidBust()


bool Player::DidAllIn()
{
    return allIn;
} // DidAllIn()


void Player::Reset()
{
    bust  = false;
    fold  = false;
    allIn = false;
	myBet = 0;
	ClearCards();
} // Reset()


string Player::GetName()
{
    return name;
} // GetName()

double Player::GetBet()
{
    return myBet;
} // GetBet()

/* Private Stuff */
void Player::CombineCards()
{   
    allCards.clear();
    allCards = tableCards;
    allCards.push_back(holeCards[0]);
    allCards.push_back(holeCards[1]);
}

void Player::SetSB(double amnt)
{
	smallBlind = amnt;
}

void Player::SetBB(double amnt)
{
	bigBlind = amnt;
}

double Player::Call(double highBet)
{
	if((highBet - myBet) == 0)
		return Check();
	if((highBet - myBet) > money)
	{
		allIn = true;
		double temp = money;
		money = 0;
		return temp;
	}

	cout << highBet << name << " called " << (highBet - myBet) << "\n";

	money -= (highBet - myBet);
	myBet = highBet;

	return (highBet - myBet);
}//Call

double Player::Fold()
{
	fold = true;
	cout << name << " folded -- loser!\n";
	return 0.0;
}//Fold

double Player::Check()
{
	cout << name << " checked (knock-knock)\n";
	return 0.0;
}//Check

double Player::Raise(double highBet, double amnt)
{
	if((highBet - myBet) > money)
	{
		return Call(highBet);
	}else if((highBet - myBet + amnt) > money)
	{
		allIn = true;
		myBet += money;
		cout << name << " is allin, called " << (highBet - myBet) << " and raised " << (money - (highBet - myBet)) << "\n";
		double temp = money;
		money = 0.0;
		return temp;
	}

	money -= (highBet - myBet + amnt);
	cout << name << " called " << (highBet - myBet) << " and raised " << amnt << "\n";
	myBet = highBet + amnt;
	return (highBet - myBet + amnt);
}//Raise

double Player::AllIn()
{
	allIn = true;
	double temp = money;
	money = 0.0;
	return temp;
} //AllIn

int Player::GetJob()
{
    return job;
}

void Player::SetJob(int theJob)
{
    job = theJob;
}