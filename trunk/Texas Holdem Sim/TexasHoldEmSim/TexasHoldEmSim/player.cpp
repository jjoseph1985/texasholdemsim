// Player.cpp

#include "player.h"

using namespace std;

Player::Player()
{

}


Player::Player(double m,map<string, double>& preFlop, string Name): pos(-1), fold(false), bust(false), allIn(false), myBet(0)
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


double Player::Action(bool limitRaise, double currentHighBet)
{
	cout << "MEMEMEE" << currentHighBet << "\n";
	possibleTurnCards.ShuffleCard();
	possibleRiverCards.ShuffleCard();

	/*---------AI STUFF TO BE REPLACED---------*/
	int decision = (rand()%4)+1; //1=check;2=call;3=raise&call;4=fold

	//Can't raise if limited and can't check if they owe money
	while((limitRaise && decision == 3) || (currentHighBet > myBet && decision == 1))
	{
		decision = (rand()%4)+1;
	}

	cout << decision << "\n";
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


void Player::SetPos(int p)
{
    pos = p;
} // SetPos()


int Player::GetPos()
{
    return pos;
} // GetPos()

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

double Player::Call(double HighBet)
{
	if((HighBet - myBet) == 0)
		return Check();
	if((HighBet - myBet) > money)
	{
		allIn = true;
		double temp = money;
		money = 0;
		return temp;
	}

	cout << HighBet << name << " called " << (HighBet - myBet) << "\n";

	money -= (HighBet - myBet);
	myBet = HighBet;

	return (HighBet - myBet);
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

double Player::Raise(double HighBet, double amnt)
{
	cout << "HIHIHI" << HighBet << "\n";
	if((HighBet - myBet) > money)
	{
		return Call(HighBet);
	}else if((HighBet - myBet + amnt) > money)
	{
		allIn = true;
		myBet += money;
		cout << name << " is allin, called " << (HighBet - myBet) << " and raised " << (money - (HighBet - myBet)) << "\n";
		double temp = money;
		money = 0.0;
		return temp;
	}

	money -= (HighBet - myBet + amnt);
	cout << name << " called " << (HighBet - myBet) << " and raised " << amnt << "\n";
	myBet = HighBet + amnt;
	return (HighBet - myBet + amnt);
}//Raise

double Player::AllIn()
{
	allIn = true;
	double temp = money;
	money = 0.0;
	return temp;
}//Raise