#ifndef DECK_H
#define DECK_H

#include <vector>
#include <ctime>
#include <algorithm>
#include <functional>
#include "card.h"

using namespace std;

class Deck
{
	public:
		Deck();
		
		void CreateDeck();
		void Clear();
		void ShuffleCard();
		
		vector<card> deck;
};
#endif