#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "apvector.h"

class Deck
{
  public:

    Deck();           // pristine, sorted deck

    void Shuffle();   // shuffle the deck, all 52 cards present
    Card GetCard();   // get a card

    int  Size() const; // # cards left in the deck

  private:

    apvector<Card> myCards;
    int            myIndex;  // current card to deal
};

#endif