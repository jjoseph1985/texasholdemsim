#include "deck.h"

Deck::Deck()
{
   
    
    
    card c1('A', 'S');
    deck.push_back(c1);
    card c1('K', 'S');     // SPADE CARDS 
    deck.push_back(c1);
    card c1('Q', 'S');
    deck.push_back(c1);
    card c1('J', 'S');
    deck.push_back(c1);
    card c1('T', 'S');
    deck.push_back(c1);
    card c1('9', 'S');
    deck.push_back(c1);
    card c1('8', 'S');
    deck.push_back(c1);
    card c1('7', 'S');
    deck.push_back(c1);
    card c1('6', 'S');
    deck.push_back(c1);
    card c1('5', 'S');
    deck.push_back(c1);
    card c1('4', 'S');
    deck.push_back(c1);
    card c1('3', 'S');
    deck.push_back(c1);
    card c1('2', 'S');
    deck.push_back(c1);
    

    card c1('A', 'H');
    deck.push_back(c1);
    card c1('K', 'H');     // Heart CARDS 
    deck.push_back(c1);
    card c1('Q', 'H');
    deck.push_back(c1);
    card c1('J', 'H');
    deck.push_back(c1);
    card c1('T', 'H');
    deck.push_back(c1);
    card c1('9', 'H');
    deck.push_back(c1);
    card c1('8', 'H');
    deck.push_back(c1);
    card c1('7', 'H');
    deck.push_back(c1);
    card c1('6', 'H');
    deck.push_back(c1);
    card c1('5', 'H');
    deck.push_back(c1);
    card c1('4', 'H');
    deck.push_back(c1);
    card c1('3', 'H');
    deck.push_back(c1);
    card c1('2', 'H');
    deck.push_back(c1);


    card c1('A', 'C');
    deck.push_back(c1);
    card c1('K', 'C');     // CLUB CARDS 
    deck.push_back(c1);
    card c1('Q', 'C');
    deck.push_back(c1);
    card c1('J', 'C');
    deck.push_back(c1);
    card c1('T', 'C');
    deck.push_back(c1);
    card c1('9', 'C');
    deck.push_back(c1);
    card c1('8', 'C');
    deck.push_back(c1);
    card c1('7', 'C');
    deck.push_back(c1);
    card c1('6', 'C');
    deck.push_back(c1);
    card c1('5', 'C');
    deck.push_back(c1);
    card c1('4', 'C');
    deck.push_back(c1);
    card c1('3', 'C');
    deck.push_back(c1);
    card c1('2', 'C');
    deck.push_back(c1);

    
    card c1('A', 'D');
    deck.push_back(c1);
    card c1('K', 'D');     // Dimamond CARDS 
    deck.push_back(c1);
    card c1('Q', 'D');
    deck.push_back(c1);
    card c1('J', 'D');
    deck.push_back(c1);
    card c1('T', 'D');
    deck.push_back(c1);
    card c1('9', 'D');
    deck.push_back(c1);
    card c1('8', 'D');
    deck.push_back(c1);
    card c1('7', 'D');
    deck.push_back(c1);
    card c1('6', 'D');
    deck.push_back(c1);
    card c1('5', 'D');
    deck.push_back(c1);
    card c1('4', 'D');
    deck.push_back(c1);
    card c1('3', 'D');
    deck.push_back(c1);
    card c1('2', 'D');
    deck.push_back(c1);

    


 
 
}

void Deck::ShuffleCard()
{
    srand( time(NULL) );
    random_shuffle(deck.begin(), deck.end());
}

void Deck::Clear()
{
    deck.clear();
}