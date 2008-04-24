// holecards.h

#ifndef HOLE_H
#define HOLE_H


#include <string>
#include <map>

#include "card.h"

using namespace std;

class holeCards
{
    public:
        holeCards();
        void setCards( const card&, const card& );
        string getCards();
        void clear();
        card firstCard();
        card secondCard();

    private:
        string data;
}; // holeCards

#endif
