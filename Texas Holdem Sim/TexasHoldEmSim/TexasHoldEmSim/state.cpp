#include "state.h"
#include <list>
#include <iostream>

using namespace std;

State::State(list<int> ops, double pt, double ms):pot(pt),my_share(ms),gameOver(false), compout( false )
{
  list<int>::iterator i = ops.begin();
  seat temp;
  temp.amtBet = 0.0;
  while( i != ops.end() ) {
    temp.index = *i;
    players.push_back( temp );
    i++;
  }

  plturn = players.begin();
  while( plturn->index != -1 ) {
    plturn++;
  }
  plturn++;

    // MJB: Why are we doing this?  
    //lastRaiser = NULL;
}

State::State(State& cpy)
{   
    if( this != &cpy )
    {
        pot      = cpy.pot;
        my_share = cpy.my_share;
        round    = cpy.round;
        compout  = cpy.compout;
        players  = cpy.players;
        table    = cpy.table;
        gameOver = cpy.gameOver;
        compout  = cpy.compout;

        list<seat>::iterator tmpItr = cpy.players.begin();
        
        // MJB unnecessary test
        //   
	    //if( cpy.lastRaiser != NULL )
	    //{
            lastRaiser = players.begin();

            while( tmpItr != cpy.lastRaiser )
            {
                lastRaiser++;
                tmpItr++;
            }
        //} 
        
        /*
        else
        {
            lastRaiser = NULL;
        }
        */

	    plturn = players.begin();
	    tmpItr = cpy.players.begin();
        
        while( tmpItr != cpy.plturn )
        {
	        plturn++;
	        tmpItr++;
	    }
    }
}

void State::Fold()
{
  cerr << "folding cur player" << endl;
    list<seat>::iterator human_iter;
    if( plturn->index == -1)
    {
      cerr << "marking compout"<< endl;
        compout = true;
    }
    else
    {
        players.erase(plturn);
    }
    updateRound(false);
}


void State::Bet()
{   
  cerr << "betting cur player" << endl;
  if( round == 1 ) {
    currBet++;
  } else {
    currBet += 2;
  }

  if( plturn->index == -1)
  {
      my_share += currBet;    
  }

  pot += currBet;

  updateRound( false );
}

void State::Call()
{    
  cerr << "calling cur player" << endl;
  if( plturn->index == -1)
  {
      my_share += currBet;    
  }

  pot += currBet;
  updateRound( true );
}

double State::winslosses()
{
    return winnings;
}


int State::getIndex( int n ) {
  list<seat>::iterator itr = players.begin();
  for( int i = 0; i < n; i++ ) {
    itr++;
  }
  return itr->index;
}

void State::setHole( int n, holeCards hc ) {
  list<seat>::iterator itr = players.begin();
  for( int i = 0; i < n; i++ ) {
    itr++;
  }
  itr->cards = hc;
}

void State::dealCard( string s ) {
  card c;
  c.setVal( s[0], s[1] );
  table.push_back( c );
}

void State::updateRound( bool called ) {
  list<seat>::iterator next = plturn;
  next++;
  if( next == lastRaiser && currBet == 2 ) {
    round++;
  } else if( plturn == lastRaiser && called == true ) {
    round++;
  }
  if( round == 4 ) {
    cerr << "   round == 4" << endl;
    gameOver == true;
  } else if( compout ) {
    cerr << "   comp is out" << endl;
    gameOver == true;
  } else if( players.size() == 1 && compout == false ) {
    cerr << "   only comp left" << endl;
    gameOver = true;
  }

  if( gameOver ) {
    pickWinner();
  }

  plturn++;
  if( plturn == players.end() ) plturn = players.begin();
}

void State::pickWinner() {
  if( compout ) {
    winnings = -1 * my_share;
  } else if( players.size() == 1 && compout == false ) {
    winnings = pot - my_share;
  } else {

    vector<hand> theHands;
    hand tmpHand;
    list<seat>::iterator itr = players.begin();
    while( itr != players.end() ) {
      tmpHand.init( table[0], table[1], table[2], table[3], table[4] );
      tmpHand.addCard( itr->cards.firstCard() );
      tmpHand.addCard( itr->cards.secondCard() );     
      theHands.push_back( tmpHand );
      itr++;
    }

    int winnerIndex = 0;
    int tieCount = 0;
    for( int i = 1; i <theHands.size(); i++ ) {
      if( theHands[i].beats( theHands[ winnerIndex ] ) ) {
	winnerIndex = i;
	tieCount = 0;
      } else if( theHands[i].ties( theHands[ winnerIndex ] ) ) {
	winnerIndex = i;
	tieCount++;
      }
    }

    if( winnerIndex == theHands.size() - 1 ) {
      if( tieCount == 0 ) {
        winnings = pot - my_share;
      } else {
	winnings = ( pot - my_share ) / tieCount;
      }
    } else {
      winnings = -1 * my_share;
    }

  }
}
