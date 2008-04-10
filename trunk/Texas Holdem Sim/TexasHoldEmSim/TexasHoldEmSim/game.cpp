// game.cpp

#include <vector>
#include <string>
#include <fstream>
#include "game.h"
#include "Round.h"
#include <iostream>

using namespace std;

game::game( struct GameFlow* gf ): potSize(0), currentBet(0), numPlayers(0), handsPlayed(0),
				   dealerNum(1), activePlayer(1), numCardsDealt(0), flow(gf)
{
  genTable();
}

void game::init( int num, const vector<int>& stacks , int dealerNumber) {

  numPlayers = num;
  for( int n = 0; n < num-1; n++){
    humanPlayer   temp;
    humans.push_back( temp );
  }
  cerr << " number of humans created == " << humans.size() << endl;
  for(int i = 0; i < num-1; i++ ) {
    humans[i].addChips( stacks[i+1] );
    humans[i].pointToTable( &odds );
  }
  teddyKGB.addChips( stacks[0] );

  vector<humanPlayer* > opps( humans.size() );
  for( int j = 0; j < humans.size(); j++ )
    opps[j] = &humans[j];
  teddyKGB.pointToOpponents( opps );

  hole.clear();
  hole.resize(0);
  potSize = 0;
  currentBet = 0;
  dealerNum = dealerNumber - 1;
  activePlayer = 1;
  numCardsDealt = 0;
  handsPlayed = 0;

  newHand();
}

double game::stackSize( int n ) {
  if( n==0 )
    return teddyKGB.stackSize();
  else
    return humans[n-1].stackSize();
}

void game::betRaise( double amnt ) {

  // depending on round, need to increment this again
  ////currentBet++;

  if( activePlayer == 0 )
    teddyKGB.betRaise( amnt );
  else
    humans[activePlayer-1].betRaise( amnt );

  ////potSize += currentBet;
  potSize += amnt;

  activePlayer = (activePlayer+1)%numPlayers;
  while( flow->isFolded( activePlayer ) ) {
    activePlayer = (activePlayer+1)%numPlayers;
  }
}

void game::callCheck( double amnt ) {
  if( activePlayer == 0 )
    teddyKGB.checkCall( amnt );
  else
    humans[activePlayer-1].checkCall( amnt );
  
  ////potSize += currentBet;
  potSize += amnt;

  activePlayer = (activePlayer+1)%numPlayers;
  while( flow->isFolded( activePlayer ) ) {
    activePlayer = (activePlayer+1)%numPlayers;
  }
}

void game::fold() {
  if( activePlayer == 0 ) {
    teddyKGB.fold();
  } else {
    humans[activePlayer-1].fold();
    if( flow->roundNum == 1 ) {
      humans[activePlayer-1].foldBeforeFlop();
    }
  }

  activePlayer = (activePlayer+1)%numPlayers;
  while( flow->isFolded( activePlayer ) ) {
    activePlayer = (activePlayer+1)%numPlayers;
  }

}

void game::newHand() {
  int b1, b2;

  teddyKGB.clearCards();
  handsPlayed++;
  teddyKGB.unfold();
  hole.clear();
  hole.resize(0);
  for(int i = 0; i < numPlayers; ++i ) {
    humans[i].unfold();
    humans[i].addFlopSeen();
  }
  dealerNum++;
  if( dealerNum == numPlayers )
    dealerNum = 0;

  b1 = (dealerNum+1) % numPlayers;
  b2 = (dealerNum+2) % numPlayers;
  
  // small blind
  if( b1 == 0 )
    teddyKGB.betRaise(.5);
  else
    humans[b1].betRaise(.5);

  flow->player[b1].second = .5;

  // big blind
  if( b2 == 0 )
    teddyKGB.betRaise(1);
  else
    humans[b2].betRaise(1);
  
  flow->player[b2].second = 1.0;

  potSize = 1.5;
  ////currentBet = 1;

  // next player is active
  activePlayer = (b2+1) % numPlayers;
}

void game::dealCard( string val ) {
  numCardsDealt++;
  card card1( val[0], val[1] );
  teddyKGB.addCard( card1 );
  activePlayer = dealerNum+1;
}

void game::pickWinner( int n ) {
  if( n == 0 )
    teddyKGB.wonHand( potSize );
  else
    humans[n-1].wonHand( potSize );
}

void game::addHole( string c ) {
  card card1( c[0], c[1] );
  hole.push_back( card1 );
  if(hole.size() == 2) {
    teddyKGB.setHoleCards(hole[0],hole[1]);
  }
}

enum actionNames game::think() {
  teddyKGB.setDealer( dealerNum );
  int seatNum = ( numPlayers - dealerNum ) -2;
  if( seatNum <= 0 ) {
    seatNum += numPlayers;
  }

  teddyKGB.setSeatNumber(seatNum);

  return teddyKGB.makeDec();
  // output to simlation box?
}

void game::genTable() {
	ifstream file;
	file.open("odds.txt");
	string hole, tmp;
	double weight;
	string a, b;

	odds.clear();
	
	for (int i = 0; i < 169; i ++)
	{
		file >> hole;
		file >> weight;
		weight = weight / 31.5;

		a = hole[0];
		b = hole[1];

		if( hole.length() == 2 ) {
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

		} else { // hole.length() == 3
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

	cerr << "human weight table size = "<<odds.size()<<endl;

}
