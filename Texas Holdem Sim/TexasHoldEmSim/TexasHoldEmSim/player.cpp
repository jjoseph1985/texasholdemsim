// Player.cpp

#include "player.h"

using namespace std;

Player::Player()
{

}


Player::Player(double m,map<string, double>& preFlop, string Name): job(-1), fold(false), bust(false), allIn(false), raised(false), myBet(0)
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


double Player::Action(bool limitRaise, double currentHighBet, bool amHole, bool amFirstIter)
{
	possibleTurnCards.ShuffleCard();
	possibleRiverCards.ShuffleCard();
	
	if(job==SMALLBLIND && amFirstIter && amHole)
	{
	    if(smallBlind > money)
	    {
	        allIn = true;
	        double temp = money;
	        myBet += money;
	        money = 0.0;
	        cout << name << " is the small blind but not enough $$$, so allIn with" << temp << "\n";
	        return temp;
	    }else
	    {
	        money -= smallBlind;
	        myBet += smallBlind;
	        cout << name << " is the small blind and is forced to bet " << smallBlind << "\n";
	        return smallBlind;
	    }
	}
	else if(job==BIGBLIND && amFirstIter && amHole)
	{
	    if(bigBlind > money)
	    {
	        allIn = true;
	        double temp = money;
	        myBet += money;
	        money = 0.0;
	        cout << name << " is the big blind but not enough $$$, so allIn with" << temp << "\n";
	        return temp;
	    }else
	    {
	        money -= bigBlind;
	        myBet += bigBlind;
	        cout << name << " is the big blind and is forced to bet " << bigBlind << "\n";
	        return bigBlind;
	    }
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
			return Raise(currentHighBet, 11);
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

bool Player::DidRaised()
{
    return raised;
} // DidRaised()


void Player::Reset()
{
    bust  = false;
    fold  = false;
    allIn = false;
	myBet = 0;
	ClearCards();
} // Reset()

void Player::ResetRaised()
{
    raised = false;
} // ResetRaised()

void Player::SetBusted()
{
    bust = true;
} // SetBusted()

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

double Player::Call(double theHighBet)
{
    double rval = 0.0;
    
	if((theHighBet - myBet) == 0)  //you idiot, you meant check!
	{
		rval = Check();
	}	
	else if((theHighBet - myBet) > money)   //if you don't have enough money to call
	{
		allIn = true;
		rval = money;
		money = 0.0;
	    cout << name << " went all in with " << rval << "\n";
	}
	else
	{
        rval = (theHighBet - myBet);
	    money -= rval;
	    myBet = theHighBet; 
	    cout << name << " called the bet of " << theHighBet << "\n";
    }
    
    return rval;
    
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

double Player::Raise(double theHighBet, double amnt)
{
    double rval = 0.0;

	if((theHighBet - myBet) > money) // Not Enough $$ to raise, much less call, all in buddy
	{
		rval = Call(theHighBet);
	}
	else if((theHighBet - myBet + amnt) > money) // Don't have enough to call AND raise how much you want
	{
		allIn = true;
		myBet += money;
		rval = money;
		money = 0.0;
		cout << name << " went all in with " << rval << "\n";
		raised = true;
	}
	else
	{
        rval = (theHighBet - myBet + amnt);
	    money -= rval;
	    cout << name << " called the bet of " << (theHighBet - myBet) << " and raised " << amnt << "\n";
	    myBet += rval;
	    raised = true;
	}
	
	return rval;
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