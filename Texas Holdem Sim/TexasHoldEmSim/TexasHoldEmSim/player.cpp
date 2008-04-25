// player.cpp

#include "player.h"

using namespace std;


Player::Player(double m): money(m), pos(-1), fold(false), bust(false), allIn(false)
{ 

} // Player()


Player::~Player()
{

} // ~Player()

        
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
    else if(loc == TABLECARDS)
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
    if(limitAction)
    {
    
    }
    else
    {
    
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

} // Reset()


void Player::SetPos(int p)
{
    pos = p;
} // SetPos()


int Player::GetPos()
{
    return pos;
} // GetPos()


/************************/

#if 0

// MJB: Sudo random right now...
enum actionNames Player::makeDec()
{ 
    int dec;
    dec = rand()%100 + 1;
    handType current;


    if( tablecards.size() == 0 )
    {
        return preflopDec();
    } 
    else
    {	
        //Back up for when the simulator doesn't work
        current = myHand.getType();		//I think you can infer that it isn't working
        if (current.getType() < 3)		//gets the best hand and adjusts weighting of 
        {					//the random number depending on how lucrative of the hand
            if ( dec >= 1 && dec <25)
                return FOLD;
            else if ( dec >= 25 && dec <50)
                return RAISE;
            else if (dec >= 50 && dec < 75)
                return CHECK;
            else if (dec >= 75 && dec < 100)
                return CALL;
        }
        else if (current.getType() < 6)
        {
            if ( dec >= 1 && dec <10)
                return FOLD;
            else if ( dec >= 10  && dec <40)
                return RAISE;
            else if (dec >= 40 && dec < 65)
                return CHECK;
            else if (dec >= 65 && dec < 100)
                return CALL;
          }	
        else  //The best cards, these will never fold
        {
            if ( dec >= 0  && dec <40)
                return RAISE;
            else if (dec >= 40 && dec < 55)
                return CHECK;
            else if (dec >= 55 && dec < 100)
                return CALL;
        }
    }
} // makeDec()

//Partially functional as of this time
//They are no longer called so that we can turn in fully executable code
enum actionNames Player::simulate()
{
    // cerr << "Enter simulate()" << endl;	//Lots of debugging going on

    list<int> activePlayers;
    
    // cerr << "X " << dealerNum << " X" << endl;
    // cerr << "Y " << opposition.size() << " Y" << endl;
    
    for(int i=dealerNum+1; i<opposition.size(); i++ )
    {
        if( ! opposition[i]->checkBust() && ! opposition[i]->checkFold() )
            activePlayers.push_back( i );
    }
    
    activePlayers.push_back( -1 );
    // cerr << "(middle)";
    
    for(int j=1; j<dealerNum+1; j++ )
    {
        if( ! opposition[j]->checkBust() && ! opposition[j]->checkFold() )
            activePlayers.push_back( j );
    }

    //cerr << "  created player list" << endl;

    Table s(activePlayers,potSize,0.0);
    
    for( int k = 0; k < tablecards.size(); k++ )
    {
        s.dealCard( tablecards[k].whatcard() );
    }
    
    s.setRound( tablecards.size() - 2 );

    //cerr << "  initialized state" << endl;
	    //Creates the initial states and then begins to pick options
    
    Table poss1( s );
    Table poss2( s );
    poss1.Bet();
    poss2.Call();

    //cerr << "  copied states" << endl;
	
	//Calls to sim begin the basic simulator
    double EVfold = 0.0;
    //cerr << " ------- BET -------" << endl;
    double EVbet = sim( poss1 );
    //cerr << " ------- CALL -------" << endl;
    double EVcall = sim( poss2 );

    if( EVfold > EVbet && EVfold > EVcall )
    {
        return FOLD;
    } 
    else if ( EVbet > EVfold && EVbet > EVcall )
    {
        return BET;
    } 
    else
    {
        return CALL;
    }
} // simulate

double Player::sim( Table& st ) {

    //cerr << "entered sim" << endl;

    double ev, evTemp;
    int numHumans = st.numberPlayers() - 1;
    double randProb( 0.0 );
    double actualProb( 0.0 );
    card c1, c2;
    holeCards possHole;
    bool cardsFound( false );
    map<string, bool> tmpDeck;
    string s1, s2;
    int n1, n2;

    cerr << "opposition size ==" << opposition.size() << endl;
    
    // MJB: The comp AI, after the flop?? currently = 4
    //      Change NUMTRIALS to change how "smart" a player is
    for(int k = 0; k < NUMTRIALS; k++)
    {

        cerr << "Dealing trial " << k << endl;
        /* DEALIN' CARDS */
        tmpDeck = aDeck;

        for( int i = 0; i < numHumans + 1; i++ )
        {
            cerr << "human number " << i << "(st.getIndex="<<st.getIndex(i)<<")" <<endl;
            system("sleep .75");
            
            if( st.getIndex( i ) != -1 )
            {
                //randProb = rand() / double(MAX_INT); // ?
                randProb = ( double(rand()) / double(RAND_MAX) );
                possHole.clear();
                ///cerr<<"randProb="<< randProb<<endl;
                do
                {
                    n1 = rand() % 52; //cerr << "(" << n1 << ")";
                    n2 = rand() % 52; //cerr << "(" << n2 << ")";
                    s1 = bDeck[n1]; //cerr << "[" << s1 << "]";
                    s2 = bDeck[n2]; //cerr << "[" << s2 << "]";
                    
                    if( tmpDeck[s1] == true && tmpDeck[s2] == true && n1 != n2 )
                    {
                        c1.setVal( s1[0], s1[1] );
                        c2.setVal( s2[0], s2[1] );
                        possHole.setCards( c1, c2 );
                        actualProb = opposition[st.getIndex(i)]->getWgt( possHole );
                        ///cerr<<"("<<actualProb<<")"<<endl;
                        
                        if( actualProb > randProb )
                        {
                            st.setHole( i, possHole );
                            tmpDeck[ c1.whatcard() ] = false;
                            tmpDeck[ c2.whatcard() ] = false;
                            cardsFound = true;
                        }
                    }
                }
                while( !cardsFound);
            }
      
            cardsFound = false;
        } // for

        for( int j = tablecards.size(); j < 5; j++ )
        {
            n1 = rand() % 52;
            s1 = bDeck[n1];
            
            if( tmpDeck[s1] = true )
            {
                st.dealCard( s1 );
                tmpDeck[s1] = false;
            } 
            else 
            {
                j--;
            }
        } // for

        evTemp = trial( st );
        cerr << "    EV = " << evTemp << endl;
        ev += evTemp;;
    } // for
    
    ev = ev / double(NUMTRIALS);
    //cerr << "  Final EV = " << ev << endl;
    return ev;
    
} // sim()

double Player::trial( Table& st )
{
    cerr << "enter trial" << endl;

    if( st.isGameOver() )
    {
        cerr << "game over" << endl;
        return st.amtWon();
    }
    else
    {
        cerr << "make s1" << endl;
        Table s1( st );
        cerr << "make s2" << endl;
        Table s2( st );
        cerr << "make s3" << endl;
        Table s3( st );
        s1.Fold();
        s2.Bet();
        s3.Call();
        
        return ( trial( s1 ) + trial( s2 ) + trial( s3 ) ) / 3.0;
    }
} // trial()


// MJB: bonus points for figuring this out...
/* Not considering difficulty at the moment, also decision are deterministic =( */
enum actionNames Player::preflopDec() {

    int numPlayers( opposition.size() + 1 );
    enum posType position( setPosition( numPlayers ) );
    enum actionNames act( FOLD );

    //Groups for the flop 
    static double grp1 = .606; // 19.09 / 31.5
    static double grp2 = .528; // 16.64 / 31.5
    static double grp3 = .509; // 16.06 / 31.5
    static double grp4 = .472; // 14.87 / 31.5
    static double grp5 = .394; // 12.42 / 31.5
    static double grp6 = .353; // 11.13 / 31.5
    static double grp7 = .339; // 10.69 / 31.5
    static double grp8 = .315; //  9.93 / 31.5

    double myWgt = weightTable[myCards.getCards()];
    //Get our position and determine what our weight is goning to be
    if( position == EARLY )
    {
        if( !betPlaced )
        {
            // call w/ 1-4
            if( myWgt > grp4 ) 
                act = CALL;
        }
        else if( !raiseMade )
        {
            // call w/ 1-4
            if( myWgt > grp4 ) 
            act = CALL; 
        }
        else
        {
            // call w/ 1-3
            if( myWgt > grp3 ) 
            act = CALL;
        }
    }
    else if( position == MIDDLE )
    {
        if( !betPlaced )
        {
            // call w/ 1-5
            if( myWgt > grp5 ) 
                act = CALL;
        } 
        else if( !raiseMade )
        {
          // raise w/ 1-3
          // call w/ ????
          if( myWgt > grp3 ) 
              act = RAISE;
          // ??
        } 
        else 
        {
          // ????
        }
    } 
    else if( position == LATE ) 
    {
        if( ! betPlaced )
        {
            // raise w/ 1-7
            if( myWgt > grp7 ) 
                act = RAISE;
        } 
        else if( !raiseMade )
        {
            // raise w/ 1-3
            // call w/ 4-5
            if( myWgt > grp3 ) 
                act = RAISE;
            else if( myWgt > grp5 ) 
                act = CALL;
        }
        else
        {
            // raise w/ 1
            // call w/ 2-3
            if( myWgt > grp1 ) 
                act = RAISE;
            else if( myWgt > grp3 ) 
                act = CALL;
        }
    } 
    else
    { // if( position == BLINDS ) {
           // repeat LATE behavior
        if( ! betPlaced )
        {
            // raise w/ 1-7
            if( myWgt > grp7 ) 
                act = RAISE;
        }
        else if( !raiseMade )
        {
            // raise w/ 1-3
            // call w/ 4-5
            if( myWgt > grp3 ) 
                act = RAISE;
            else if( myWgt > grp5 ) 
                act = CALL;
        } 
        else
        {
            // raise w/ 1
            // call w/ 2-3
             if( myWgt > grp1 ) 
                 act = RAISE;
             else if( myWgt > grp3 ) 
                  act = CALL;
        }
    }
    
    return act;
} // preflopDec



#endif

