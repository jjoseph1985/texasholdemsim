#include "deck.h"

void Deck::Deck(vector<card>& deck)
{

}

void Deck::ShuffleCard()
{
    srand( time(NULL) );

    // vector<string>deck; // Intializes the vector card

    deck.push_back(card  card1('A', 'S')); //Add Spades
    deck.push_back(card  card2('K', 'S'));
    deck.push_back(card  card3('Q', 'S'));
    deck.push_back(card  card4('J', 'S'));
    deck.push_back(card  card5('10','S'));
    deck.push_back(card  card6('9', 'S'));
    deck.push_back(card  card7('8', 'S'));
    deck.push_back(card  card8('7', 'S'));
    deck.push_back(card  card9('6', 'S'));
    deck.push_back(card card10('5', 'S'));
    deck.push_back(card card11('4', 'S'));
    deck.push_back(card card12('3', 'S'));
    deck.push_back(card card13('2', 'S'));

    deck.push_back(card card14('A', 'H')); // Add Hearts
    deck.push_back(card card15('K', 'H'));
    deck.push_back(card card16('Q', 'H'));
    deck.push_back(card card17('J', 'H'));
    deck.push_back(card card18('10','H'));
    deck.push_back(card card19('9', 'H'));
    deck.push_back(card card20('8', 'H'));
    deck.push_back(card card21('7', 'H'));
    deck.push_back(card card22('6', 'H'));
    deck.push_back(card card23('5', 'H'));
    deck.push_back(card card24('4', 'H'));
    deck.push_back(card card25('3', 'H'));
    deck.push_back(card card26('2', 'H'));

    deck.push_back(card card27('A', 'C')); // Add Clubs
    deck.push_back(card card28('K', 'C'));
    deck.push_back(card card29('Q', 'C'));
    deck.push_back(card card30('J', 'C'));
    deck.push_back(card card31('10','C'));
    deck.push_back(card card32('9', 'C'));
    deck.push_back(card card33('8', 'C'));
    deck.push_back(card card34('7', 'C'));
    deck.push_back(card card35('6', 'C'));
    deck.push_back(card card36('5', 'C'));
    deck.push_back(card card37('4', 'C'));
    deck.push_back(card card38('3', 'C'));
    deck.push_back(card card39('2', 'C'));

    deck.push_back(card card27('A', 'C')); // Add Clubs
    deck.push_back(card card28('K', 'C'));
    deck.push_back(card card29('Q', 'C'));
    deck.push_back(card card30('J', 'C'));
    deck.push_back(card card31('10','C'));
    deck.push_back(card card32('9', 'C'));
    deck.push_back(card card33('8', 'C'));
    deck.push_back(card card34('7', 'C'));
    deck.push_back(card card35('6', 'C'));
    deck.push_back(card card36('5', 'C'));
    deck.push_back(card card37('4', 'C'));
    deck.push_back(card card38('3', 'C'));
    deck.push_back(card card39('2', 'C'));
    
    deck.push_back(card card40('A', 'D')); // Add Diamonds
    deck.push_back(card card41('K', 'D'));
    deck.push_back(card card42('Q', 'D'));
    deck.push_back(card card43('J', 'D'));
    deck.push_back(card card44('10','D'));
    deck.push_back(card card45('9', 'D'));
    deck.push_back(card card46('8', 'D'));
    deck.push_back(card card47('7', 'D'));
    deck.push_back(card card48('6', 'D'));
    deck.push_back(card card49('5', 'D'));
    deck.push_back(card card50('4', 'D'));
    deck.push_back(card card51('3', 'D'));
    deck.push_back(card card52('2', 'D'));

    random_shuffle(deck.begin(), deck.end());
}