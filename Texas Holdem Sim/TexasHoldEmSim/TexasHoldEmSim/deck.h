#ifndef DECK_H
#define DECK_H

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <functional>


using namespace std;

class Deck
{
public:
    Deck();
    void ShuffleCard();
    vector<string> deck;

};


#endif