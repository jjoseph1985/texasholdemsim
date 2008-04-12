// holecards.cpp

#include "holecards.h"


holeCards::holeCards()
{
    // empty 
}


void holeCards::setCards( const card& c1, const card& c2 )
{
    if( c1.getfacenum() > c2.getfacenum() )
        data = c1.whatcard() + c2.whatcard();
    else
        data = c2.whatcard() + c1.whatcard();
}

string holeCards::getCards()
{
    return data;
}

card holeCards::firstCard()
{
    card c;
    c.setVal( data[0], data[1] );
    return c;
}

card holeCards::secondCard() {
    card c;
    c.setVal( data[2],  data[3] );
    return c;
}
