// comp.cpp

#include "comp.h"

#define MAX_INT  32767

using namespace std;

// MJB: This is incredible stupid
compPlayer::compPlayer():chipCount(0), handsPlayed(0), flopsSeen(0), out(false), bust(false), 
                         betPlaced( false ), raiseMade( false ), posAtTable(0),
                         potSize(0), dealerNum(0)
{ 
  aDeck["As"] = true; bDeck[0] = "As";
  aDeck["Ks"] = true; bDeck[1] = "Ks";
  aDeck["Qs"] = true; bDeck[2] = "Qs";
  aDeck["Js"] = true; bDeck[3] = "Js";
  aDeck["Ts"] = true; bDeck[4] = "Ts";
  aDeck["9s"] = true; bDeck[5] = "9s";
  aDeck["8s"] = true; bDeck[6] = "8s";
  aDeck["7s"] = true; bDeck[7] = "7s";
  aDeck["6s"] = true; bDeck[8] = "6s";
  aDeck["5s"] = true; bDeck[9] = "5s";
  aDeck["4s"] = true; bDeck[10] = "4s";
  aDeck["3s"] = true; bDeck[11] = "3s";
  aDeck["2s"] = true; bDeck[12] = "2s";		//Intializes the deck for simulation purposes

  aDeck["Ah"] = true; bDeck[13] = "Ah";
  aDeck["Kh"] = true; bDeck[14] = "Kh";
  aDeck["Qh"] = true; bDeck[15] = "Qh";
  aDeck["Jh"] = true; bDeck[16] = "Jh";
  aDeck["Th"] = true; bDeck[17] = "Th";
  aDeck["9h"] = true; bDeck[18] = "9h";
  aDeck["8h"] = true; bDeck[19] = "8h";
  aDeck["7h"] = true; bDeck[20] = "7h";
  aDeck["6h"] = true; bDeck[21] = "6h";
  aDeck["5h"] = true; bDeck[22] = "5h";
  aDeck["4h"] = true; bDeck[23] = "4h";
  aDeck["3h"] = true; bDeck[24] = "3h";
  aDeck["2h"] = true; bDeck[25] = "2h";

  aDeck["Ac"] = true; bDeck[26] = "Ac";
  aDeck["Kc"] = true; bDeck[27] = "Kc";
  aDeck["Qc"] = true; bDeck[28] = "Qc";
  aDeck["Jc"] = true; bDeck[29] = "Jc";
  aDeck["Tc"] = true; bDeck[30] = "Tc";
  aDeck["9c"] = true; bDeck[31] = "9c";
  aDeck["8c"] = true; bDeck[32] = "8c";
  aDeck["7c"] = true; bDeck[33] = "7c";
  aDeck["6c"] = true; bDeck[34] = "6c";
  aDeck["5c"] = true; bDeck[35] = "5c";
  aDeck["4c"] = true; bDeck[36] = "4c";
  aDeck["3c"] = true; bDeck[37] = "3c";
  aDeck["2c"] = true; bDeck[38] = "2c";

  aDeck["Ad"] = true; bDeck[39] = "Ad";
  aDeck["Kd"] = true; bDeck[40] = "Kd";
  aDeck["Qd"] = true; bDeck[41] = "Qd";
  aDeck["Jd"] = true; bDeck[42] = "Jd";
  aDeck["Td"] = true; bDeck[43] = "Td";
  aDeck["9d"] = true; bDeck[44] = "9d";
  aDeck["8d"] = true; bDeck[45] = "8d";
  aDeck["7d"] = true; bDeck[46] = "7d";
  aDeck["6d"] = true; bDeck[47] = "6d";
  aDeck["5d"] = true; bDeck[48] = "5d";
  aDeck["4d"] = true; bDeck[49] = "4d";
  aDeck["3d"] = true; bDeck[50] = "3d";
  aDeck["2d"] = true; bDeck[51] = "2d";

  initTable( weightTable );
  srand( 0 );
} // compPlayer()

void compPlayer::addChips(int amt)
{
	chipCount += amt;		//For adding chips during the game
	bust = false;
} // addChips()

double compPlayer::stackSize()
{
	return chipCount;		
} // chipCount()

void compPlayer::setHoleCards(card a, card b)
{
	myCards.clear();
	myCards.setCards(a, b);
} // setHoleCards()

void compPlayer::fold()
{
    out = true;
} // fold()

void compPlayer::betRaise( double amt )
{
  if(!out && (amt > chipCount) && !bust)
    {
        //game.addPot(amt);				//Perform basic checks and then decrement chip count
        chipCount -= amt;
    }
    else if(amt>chipCount)
    {
        ; // MJB: do nothing
    }
}  // betRaise()

void compPlayer::checkCall( double amt )
{					//Same as in the bet raise function
    if(!out && amt>chipCount && !bust)
    {
    //game.addPot(amt);
        chipCount -= amt;
    }
    else if(amt>chipCount)
    {
        ; // MJB: do nothing
    }   
} // checkCall()

void compPlayer::busted()
{
    bust = true;
} // busted()

void compPlayer::newHand()
{
	myCards.clear();		//A mid game initializer that sets up the computer for a new hand
	tablecards.clear();
	myHand.clear();
	betPlaced  = false;
	raiseMade  = false;
	posAtTable = 0;    // set this here? or allow game to set it?
    dealerNum  = 0;     //     ditto above
	potSize    = 0.0;

	map<string,bool>::iterator tmp = aDeck.begin();
	while( tmp != aDeck.end() )
	{
	    tmp->second = true;			//Reset the deck for the simulation
	    tmp++;
	}
} // newHand()

void compPlayer::addCard(card next)
{	
    //Adds a card for use in the computers hand
	tablecards.push_back(next);
	
	if( tablecards.size() == 3)
	{
        myHand.init( tablecards[0], tablecards[1], tablecards[2],
		myCards.firstCard(), myCards.secondCard() );
	}
	else if (tablecards.size() > 3)
	{
		myHand.addCard(tablecards[tablecards.size()-1]);
	}
	
	aDeck[next.whatcard()] = false;
} // addCard()

//reset function
void compPlayer::clearCards()
{
    myCards.clear();
    tablecards.clear();
    myHand.clear();
} // clearCards()

void compPlayer::unfold()
{
	out = false;
} // unfold()

bool compPlayer::checkBust()
{
	return bust;
} // checkBust()

bool compPlayer::checkFold()
{
	return out;
}  // checkFold()

// MJB: Sudo random right now...
enum actionNames compPlayer::makeDec()
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
enum actionNames compPlayer::simulate()
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

    State s(activePlayers,potSize,0.0);
    
    for( int k = 0; k < tablecards.size(); k++ )
    {
        s.dealCard( tablecards[k].whatcard() );
    }
    
    s.setRound( tablecards.size() - 2 );

    //cerr << "  initialized state" << endl;
	    //Creates the initial states and then begins to pick options
    
    State poss1( s );
    State poss2( s );
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

double compPlayer::sim( State& st ) {

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

double compPlayer::trial( State& st )
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
        State s1( st );
        cerr << "make s2" << endl;
        State s2( st );
        cerr << "make s3" << endl;
        State s3( st );
        s1.Fold();
        s2.Bet();
        s3.Call();
        
        return ( trial( s1 ) + trial( s2 ) + trial( s3 ) ) / 3.0;
    }
} // trial()


// MJB: bonus points for figuring this out...
/* Not considering difficulty at the moment, also decision are deterministic =( */
enum actionNames compPlayer::preflopDec() {

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


//Find where the computer player is in the latest hand so as to better figure what to do on the flop
enum posType compPlayer::setPosition( const int& numPlayers )
{
    enum posType position;

    if( numPlayers == 9 )
    {
        if( posAtTable == 1 || posAtTable == 2 )
            position = EARLY;
        else if( posAtTable == 3 || posAtTable == 4 || posAtTable == 5 )
            position = MIDDLE;
        else if( posAtTable == 6 || posAtTable == 7 )
            position = LATE;
        else if( posAtTable == 8 || posAtTable == 9 )
            position = BLINDS;
    }
    else if( numPlayers == 8 )
    {
        if( posAtTable == 1 || posAtTable == 2 )
            position = EARLY;
        else if( posAtTable == 3 || posAtTable == 4 )
            position = MIDDLE;
        else if( posAtTable == 5 || posAtTable == 6 )
            position = LATE;
        else if( posAtTable == 7 || posAtTable == 8 )
            position = BLINDS;
    }
    else if( numPlayers == 7 )
    {
        if( posAtTable == 1 || posAtTable == 2 )
            position = EARLY;
        else if( posAtTable == 3 || posAtTable == 4 )
            position = MIDDLE;
        else if( posAtTable == 5 )
            position = LATE;
        else if( posAtTable == 6 || posAtTable == 7 )
            position = BLINDS;
    }
    else if( numPlayers == 6 )
    {
        if( posAtTable == 1 )
            position = EARLY;
        else if( posAtTable == 2 || posAtTable == 3 )
            position = MIDDLE;
        else if( posAtTable == 4 )
            position = LATE;
        else if( posAtTable == 5 || posAtTable == 6 )
            position = BLINDS;
    }
    else if( numPlayers == 5 )
    {
        if( posAtTable == 1 )
            position = EARLY;
        else if( posAtTable == 2 )
            position = MIDDLE;
        
        if( posAtTable == 3 )
            position = LATE;
        if( posAtTable == 4 || posAtTable == 5 )
            position = BLINDS;
    } 
    else if( numPlayers == 4 ) 
    {
        if( posAtTable == 1 )
            position = EARLY;
        else if( posAtTable == 2 )
            position = MIDDLE;
        if( posAtTable == 3 || posAtTable == 4 )
            position = BLINDS;
    } 
    else if( numPlayers == 3 )
    {
        if( posAtTable == 1 )
            position = EARLY;
        if( posAtTable == 2 || posAtTable == 3 )
            position = BLINDS;
    }
    else
    { // if( numPlayers == 2 )
        if( posAtTable == 1 )
            position = EARLY;
        if( posAtTable == 2 )
            position = BLINDS;
    }

  return position;
  
} // setPosition()

//Initialize the weight table for use in the flop 
void compPlayer::initTable( map<string, double>& odds )
{
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

		a = hole[0];
		b = hole[1];
		weight = weight / 31.5;

		if( hole.length() == 2 )
		{
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
         }
         else
         { // hole.length() == 3
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
} // initTable()
