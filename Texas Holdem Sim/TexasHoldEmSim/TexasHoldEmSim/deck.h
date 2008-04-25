#ifndef DECK_H
#define DECK_H

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <functional>
#include "card.h"


using namespace std;

class Deck
{
	public:
		Deck(vector<card>& deck);
		void ShuffleCard();
};
#endif