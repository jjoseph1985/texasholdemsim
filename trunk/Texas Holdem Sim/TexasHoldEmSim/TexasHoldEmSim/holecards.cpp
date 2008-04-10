// hole.cpp

#include <string>
#include "holecards.h"
#include "card.h"

holeCards::holeCards( ) { }


void holeCards::setCards( const card& c1, const card& c2 ){
  if( c1.getnum2() > c2.getnum2() )
    data = c1.whatcard() + c2.whatcard();
  else
    data = c2.whatcard() + c1.whatcard();
}

string holeCards::getCards() {
  return data;
}

card holeCards::firstCard() {
  card tmp;
  tmp.setVal( data[0], data[1] );
  return tmp;
}

card holeCards::secondCard() {
  card tmp;
  tmp.setVal( data[2],  data[3] );
  return tmp;
}
