// human.cpp

#include "human.h"

using namespace std;

humanPlayer::humanPlayer(): chipCount(0), handsPlayed(0),
                                      flopsSeen(0), out(false),bust(false)
{ 
  //initTable( weightTable );
}

humanPlayer::humanPlayer(int cc = 0): chipCount(cc), handsPlayed(0),
                                      flopsSeen(0), out(false),bust(false)
{
  //initTable( weightTable );
}

void humanPlayer::addChips(int amnt)
{
	chipCount += double( amnt );
	bust = false;
}


double humanPlayer::aggressiveness()
{
    return double(raises/handsPlayed);

}

double humanPlayer::tightness()
{
    
    return double(flopsSeen/handsPlayed);
}

void humanPlayer::fold()
{
    out = true;

}

void humanPlayer::betRaise(double amt)
{
    if(!out && amt<=chipCount && !bust)
    {
    //game.addPot(amt);
    chipCount -= amt;
    }
    else if(amt>chipCount)
    {
    }
}


void humanPlayer::checkCall(double amt)
{
    if(!out && amt>chipCount && !bust)
    {
    //game.addPot(amt);
    chipCount -= amt;
    }
    else if(amt>chipCount)
    {
    }   
}

void humanPlayer::busted()
{
    bust = true;
}

map<string, double>* humanPlayer::getWeights()
{
    return weightTable;
}

void humanPlayer::updateWeights()
{

}

double humanPlayer::stackSize()
{
	return chipCount;
}

void humanPlayer::unfold()
{
	out = false;
}

bool humanPlayer::checkBust()
{
	return bust;
}

bool humanPlayer::checkFold()
{
	return out;
}

double humanPlayer::getWgt( holeCards hc ) {
  ///cerr << hc.getCards() << "--";
  return (*weightTable)[ hc.getCards() ];
}



/*
void humanPlayer::initTable( map<string, double>& odds ) {
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
*/
