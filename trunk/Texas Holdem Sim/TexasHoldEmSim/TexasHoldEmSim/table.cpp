// state.cpp

#include "table.h"


using namespace std;

Table::Table(list<int> ops, double pt, double ms): pot(pt), my_share(ms), gameOver(false), compout(false)
{
    list<int>::iterator i = ops.begin();
    seat temp;
    temp.amtBet = 0.0;
    
    while( i != ops.end() )
    {
        temp.index = *i;
        players.push_back(temp);
        i++;
    }

    plturn = players.begin();

    while( plturn->index != -1 )
    {
        plturn++;
    }
    
    plturn++;

    // MJB: This doesn't make sense  
    //lastRaiser = NULL;
}

Table::Table(Table& cpy)
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
} // Table()

void Table::Fold()
{
    // cerr << "folding cur player" << endl;
    list<seat>::iterator human_iter;
    
    if( plturn->index == -1)
    {
        // cerr << "marking compout" << endl;
        compout = true;
    }
    else
    {
        players.erase(plturn);
    }
    updateRound(false);
} // Fold()


void Table::Bet()
{   
    //cerr << "betting cur player" << endl;
    
    if( round == 1 )
    {
        currBet++;
    } 
    else
    {
        currBet += 2;
    }

    // MJB: WTF?
    if( plturn->index == -1)
    {
        my_share += currBet;    
    }

    pot += currBet;

    updateRound( false );
} // Bet()

void Table::setRound( int r )
{
    round = r;
}

int Table::numberPlayers()
{ 
    return players.size(); 
}

bool Table::isGameOver()
{ 
    return gameOver;
}

void Table::Call()
{    
    //cerr << "calling cur player" << endl;
    
    if( plturn->index == -1)
    {
        my_share += currBet;    
    }

    pot += currBet;
    updateRound( true );
} // Call()

double Table::amtWon()
{
    return winnings;
} // amtWon()


int Table::getIndex( int n )
{
    list<seat>::iterator itr = players.begin();

    // This is stupid but can't access a list any other way
    for( int i = 0; i < n; i++ )
    {
        itr++;
    }

    return itr->index;
    
} // getIndex()

void Table::setHole( int n, holeCards hc )
{
    list<seat>::iterator itr = players.begin();

    // This is stupid but can't access a list any other way
    for( int i = 0; i < n; i++ )
    {
        itr++;
    }
    
    itr->cards = hc;

} // setHole()

void Table::dealCard( string s )
{
    card c;
    c.setVal( s[0], s[1] );
    table.push_back( c );
} // dealCard

void Table::updateRound( bool called )
{
    list<seat>::iterator next = plturn;
    next++;
    
    if( next == lastRaiser && currBet == 2 )
    {
        round++;
    } 
    else if( plturn == lastRaiser && called == true )
    {
        round++;
    }
    
    if( round == 4 )
    {
        cerr << "   round == 4" << endl;
        gameOver = true;
        pickWinner();
    }
    
    // MJB: we don't want this
/*    else if( compout )
    {
        cerr << "   comp is out" << endl;
        gameOver = true;
    } 
    else if( players.size() == 1 && compout == false )
    {
        cerr << "   only comp left" << endl;
        gameOver = true;
    }

    if( gameOver )
    {
        pickWinner();
    }
*/

    plturn++;
    
    if( plturn == players.end() )
    {  
         plturn = players.begin();
    }
}

void Table::pickWinner() {
    
    if( compout )
    {
        winnings = -1 * my_share;
    } 
    else if( players.size() == 1 && compout == false )
    {
        winnings = pot - my_share;
    }
    else
    {
        vector<hand> theHands;
        hand tmpHand;
        list<seat>::iterator itr = players.begin();
        
        while( itr != players.end() )
        {
            tmpHand.init( table[0], table[1], table[2], table[3], table[4] );
            tmpHand.addCard( itr->cards.firstCard() );
            tmpHand.addCard( itr->cards.secondCard() );     
            theHands.push_back( tmpHand );
            itr++;
        }

        int winnerIndex = 0;
        int tieCount = 0;

        for( int i = 1; i < theHands.size(); i++ )
        {
            if(theHands[i].beats( theHands[winnerIndex] ))
            {
                winnerIndex = i;
                tieCount = 0;
            } 
            else if( theHands[i].ties( theHands[ winnerIndex ] ) )
            {
                winnerIndex = i;
                tieCount++;
            }
        }

        if( winnerIndex == theHands.size() - 1 ) 
        {
            if( tieCount == 0 )
            {
                winnings = pot - my_share;
            }
            else 
            {
                winnings = ( pot - my_share ) / tieCount;
            }
        } 
        else
        {
            winnings = -1 * my_share;
        }
    }
}
