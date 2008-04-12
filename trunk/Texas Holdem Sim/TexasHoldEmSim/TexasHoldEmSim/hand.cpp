// hand.cpp

#include "hand.h"

using namespace std;

hand::hand(): typeValid(false) { }

void hand::init(const card& one, const card& two, const card& three, const card& four, const card& five)
{   
    card temp('A','h');

    cards.push_back(one);
    cards.push_back(two);
    cards.push_back(three);
    cards.push_back(four);
    cards.push_back(five);
    
    // sort cards high to low via bubble sort
    for(int i = 0; i < cards.size(); i++)
        for(int j = 0; j < cards.size() -i; j++)
        {
            if(cards[j].getnum2() < cards[j+1].getnum2())
            {
                temp = cards[j];
                cards[j] = cards[j+1];
                cards[j+1] = temp;
            }
        }
    
    addcombo(0,1,2,3,4);
} // init() 

void hand::addCard( const card& next )
{
    card temp('A','h');
    card temp2('A','h');
    bool insert = false;
    int i = 0, j = 0;

    while ( i != cards.size())
    {
        if(next.getnum2() > cards[i].getnum2())
        {
          j = i;
          i = cards.size();
          insert = true;
        } 
        else
        {
            i++;
        }
    }

    if( insert )
    {
        temp = cards[j];
        cards[j] = next;
        j++;
    
        while(j != cards.size()-1)
        {
            temp2 = cards[j];
            cards[j] = temp;
            temp = temp2;
            j++;
        } 

        cards.push_back(temp);
    } 
    else
    {
        cards.push_back(next);
    }        
    
    // We now have more than 5 cards, so we have to consider all combinations        
    if( cards.size() == 6 )
    {
        addcombo(1,2,3,4,5);
        addcombo(0,2,3,4,5);
        addcombo(0,1,3,4,5);
        addcombo(0,1,2,4,5);
        addcombo(0,1,2,3,5);
    } 
    else if( cards.size() == 7 )
    {
        addcombo(2,3,4,5,6);
        addcombo(1,3,4,5,6);
        addcombo(1,2,4,5,6);
        addcombo(1,2,3,5,6);
        addcombo(1,2,3,4,6);
        addcombo(0,3,4,5,6);
        addcombo(0,2,4,5,6);
        addcombo(0,2,3,5,6);
        addcombo(0,2,3,4,6);
        addcombo(0,1,4,5,6);
        addcombo(0,1,3,5,6);
        addcombo(0,1,3,4,6);
        addcombo(0,1,2,5,6);
        addcombo(0,1,2,4,6);
        addcombo(0,1,2,3,6);
    }
} // addCard()

handType hand::getType()
{
    handType best;
    handType currType;
    int index = 0;

    for(int i = 0; i < possHands.size(); ++i )
    {
        currType = typeOf( possHands[i] );

        if( currType.beats( best ) )
        {
            best = currType;
            index = i;
        }
    }

    typeValid = true;
    return currType;  
}

// Check what kind of hand a player has: pair, 2 pairs, flush, etc.
handType hand::typeOf( const vector<card>& h )
{
    handType theType;
    
    bool flushFlag = isFlush( h, theType );
    bool straightFlag = isStraight( h, theType );

    if( straightFlag && flushFlag )
    {
        if( h[0].getnum() == 'A' )
        {
            theType.setType( RFLUSH );
        } 
        else
        {
            theType.setType( SFLUSH, h[0].getnum2() );
        }
    } 
    else if( is4kind( h, theType ) ) {}
    else if( isFull( h, theType ) ) {}
    else if( flushFlag )
    {
        theType.setType( FLUSH, h[0].getnum2(), h[1].getnum2(), h[2].getnum2(), h[3].getnum2(), h[4].getnum2() );
    } 
    else if( straightFlag ) {}
    else if( is3kind( h, theType ) ) {}
    else if( is2pair( h, theType ) ) {}
    else if( isPair( h, theType ) ) {} 
    else 
    {   // highcard
        theType.setType( JUNK, h[0].getnum2(), h[1].getnum2(), h[2].getnum2(), h[3].getnum2(), h[4].getnum2() );
    }
    
    return theType;
} // getType()

// 
void hand::addcombo( int x1, int x2, int x3, int x4, int x5 )
{
    vector<card> p(5);
    
    p[0] = cards[x1];
    p[1] = cards[x2];
    p[2] = cards[x3];
    p[3] = cards[x4];
    p[4] = cards[x5];
    possHands.push_back( p ); // MJB: This is fine. (vector of vectors)
} // addcombo


void hand::clear()
{
    cards.clear();
    myType.clear();
    possHands.clear();
    typeValid = false;
} // clear()


// MJB: Needs to be tested
bool hand::isStraight( const vector<card>& h, handType& type )
{
    bool rval = false;

    int n0 = h[0].getnum2() + 0;
    int n1 = h[1].getnum2() + 1;
    int n2 = h[2].getnum2() + 2;
    int n3 = h[3].getnum2() + 3;
    int n4 = h[4].getnum2() + 4;
    int kicker = h[0].getnum2();

    // MJB: Allow ace-low straight
    if (n0 == 14)
    {
        n0 = 1;
        kicker = h[1].getnum2();
    }
    
    // MJB: Should check for any straight
    if( n0 == n1 == n2 == n3 == n4 )
    {
        type.setType( STRAIGHT, kicker);
        rval = true;
    }
    
    return rval;
} // isStraight()    

bool hand::isFlush( const vector<card>& h, handType& type ) 
{
    bool rVal = false;
    
    if( h[0].getsuit() == h[1].getsuit() == h[2].getsuit() == h[3].getsuit() == h[4].getsuit() )
    {
        type.setType( FLUSH ); // set other values in main evaluator b/c of royal straight check
        rVal = true;
    }
    
    return rVal;
} // isFlush()

// Check if 4 of a kind. Cards are already sorted.
bool hand::is4kind( const vector<card>& h, handType& type )
{
    if( h[0].getnum() == h[1].getnum() == h[2].getnum() == h[3].getnum() )
    {
        type.setType( FOURKIND, h[0].getnum2(), h[4].getnum2() );
        return true;
    } 
    else if( h[1].getnum() == h[2].getnum() == h[3].getnum() == h[4].getnum() )
    {
        type.setType( FOURKIND, h[1].getnum2(), h[0].getnum2() );
        return true;
    }
    
    return false;
} // is4kind

bool hand::is3kind( const vector<card>& h, handType& type )
{
    if( h[0].getnum() == h[1].getnum() == h[2].getnum() )
    {
        type.setType( THREEKIND, h[0].getnum2(), h[4].getnum2(), h[3].getnum2() );
        return true;
    } 
    else if( h[1].getnum() == h[2].getnum() == h[3].getnum() )
    {
        type.setType( THREEKIND, h[1].getnum2(), h[4].getnum2(), h[0].getnum2() );
        return true;
    }
    else if( h[2].getnum() == h[3].getnum() == h[4].getnum() )
    {
        type.setType( THREEKIND, h[2].getnum2(), h[1].getnum2(), h[0].getnum2() );
        return true;
    }
    
    return false;
} // is3kind


bool hand::isFull( const vector<card>& h, handType& type )
{
    if( h[0].getnum() == h[1].getnum() == h[2].getnum() && h[3].getnum() == h[4].getnum() )
    {
        type.setType( FULL, h[0].getnum2(), h[3].getnum2() );
        return true;
    }
    else if ( h[2].getnum() == h[3].getnum() == h[4].getnum() && h[0].getnum() == h[1].getnum() )
    {
        type.setType( FULL, h[2].getnum2(), h[0].getnum2() );
        return true;
    }
    
    return false;
} // isFull

bool hand::is2pair( const vector<card>& h, handType& type )
{
    if( h[0].getnum() == h[1].getnum() && h[2].getnum() == h[3].getnum() )
    {
        type.setType( TWOPAIR, h[0].getnum2(), h[2].getnum2(), h[4].getnum2() );
        return true;
    }
    else if( h[0].getnum() == h[1].getnum() && h[4].getnum() == h[4].getnum() )
    {
        type.setType( TWOPAIR, h[0].getnum2(), h[3].getnum2(), h[2].getnum2() );
        return true;
    } 
    else if( h[1].getnum() == h[2].getnum() && h[3].getnum() == h[4].getnum() )
    {
        type.setType( TWOPAIR, h[1].getnum2(), h[3].getnum2(), h[0].getnum2() );
        return true;
    }
    return false;
} // is2pair()

bool hand::isPair( const vector<card>& h, handType& type )
{
    if( h[0].getnum() == h[1].getnum() )
    {
        type.setType( PAIR, h[0].getnum2(), h[2].getnum2(), h[3].getnum2(), h[4].getnum2() );
        return true;
    }
    else if( h[1].getnum() == h[2].getnum() )
    {
        type.setType( PAIR, h[1].getnum2(), h[0].getnum2(), h[3].getnum2(), h[4].getnum2() );
        return true;
    }
    else if( h[2].getnum() == h[3].getnum() )
    {
        type.setType( PAIR, h[2].getnum2(), h[0].getnum2(), h[1].getnum2(), h[4].getnum2() );
        return true;
    }
    else if( h[3].getnum() == h[4].getnum() )
    {
        type.setType( PAIR, h[3].getnum2(), h[0].getnum2(), h[1].getnum2(), h[2].getnum2() );
        return true;
    }
    
    return false;
} // isPair()

bool hand::beats( hand& other )
{
    handType temp = other.getType();
    return myType.beats( temp );
} // beats()

bool hand::ties( hand& other )
{
    handType temp = other.getType();
    return myType.ties( temp );
} // ties()

/***************************************************************************/

handType::handType(): label(BLANK), kick1(0),  kick2(0), kick3(0),  kick4(0),  kick5(0)
{

}

/* void setType( enum typeName tn = BLANK, int a = 0, int b = 0,
   int c = 0, int d = 0, int e = 0 ) { */
   
void handType::setType( enum typeName tn, int a, int b, int c, int d, int e )
{
    label = tn;
    kick1 = a;
    kick2 = b;
    kick3 = c;
    kick4 = d;
    kick5 = e;
}

bool handType::beats( handType& other )
{
    if( label > other.label )
    {
        return true;
    } 
    else if( label == other.label )
    {
        if( kick1 > other.kick1 )
        {
            return true;
        }
        else if( kick1 == other.kick1 )
        {
            if( kick2 > other.kick2 )
            {
                return true;
            } 
            else if( kick2 == other.kick2 )
            {
                if( kick3 > other.kick3 )
                {
                    return true;
                }
                else if( kick3 == other.kick3 )
                {
                    if( kick4 > other.kick4 )
                    {
                        return true;
                    } 
                    else if( kick4 == other.kick4 )
                    {
                        // MJB: Why is this here, we already checked kick2
                        if( kick2 > other.kick2 )
                        {
                            return true;
                        //} else if( kick2 === other.kick2 ) {
                        //  return false;
                        }
                        else
                        {
                            return false;
                        }
                    } // kick4 == 
                    else
                    {
                        return false;
                    } // kick4 <
                } // kick3 ==
                else
                {
                    return false;
                } // kick3 <
            } // kick2 == 
            else
            {
                return false;
            } // kick2 <
        } // kick1 ==
        else
        {
            return false;
        } // kick1 <
    } // label == 
    else
    {
        return false;
    } // label <
}

bool handType::ties( handType& other )
{
    rval = false;
    
    if( label == other.label && kick1 == other.kick1 && kick2 == other.kick2 
        && kick3 == other.kick3 && kick4 == other.kick4 && kick5 == other.kick5 )
    {
        rval = true;
    }
    
    return rval;
} // ties

void handType::clear()
{
    label = BLANK;
    kick1 = 0;
    kick2 = 0;
    kick3 = 0;
    kick4 = 0;
    kick5 = 0;
} // clear()
