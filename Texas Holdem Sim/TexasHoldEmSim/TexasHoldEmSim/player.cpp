// Player.cpp

#include "player.h"

using namespace std;

Player::Player()
{

}


Player::Player(double m,map<string, double>& preFlop): pos(-1), fold(false), bust(false), allIn(false)
{ 
    money = m;
	preFlopOdds = preFlop;
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
} // ClearCard()


double Player::Action(bool limitAction)
{
	possibleTurnCards.ShuffleCard();
	possibleRiverCards.ShuffleCard();

    if(limitAction)
    {
    
    }
    else
    {
    
    }
    
    return 0.0;
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

} // Reset()


void Player::SetPos(int p)
{
    pos = p;
} // SetPos()


int Player::GetPos()
{
    return pos;
} // GetPos()


/* Private Stuff */
void Player::CombineCards()
{   
    allCards.clear();
    allCards = tableCards;
    allCards.push_back(holeCards[0]);
    allCards.push_back(holeCards[1]);
}
