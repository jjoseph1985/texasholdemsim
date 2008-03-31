#ifndef PLAYER_H
#define PLAYER_H

#include <math>
#include <string>
#include "tells.h"

class Player : public Tells
{
	public:
		updateHand();
		Hand getHand();
		placeBet();
		addChips();
		bool hasFolded();
		makeHand();


	private:
		string firstName;
		string lastName;

		int skillLevel;
		int chips;
		bool folded;
		int betAmount;
		bool isDealer;
		bool isBigBlind;
		bool isSmallBlind;
        bool lastRaised;
		enum tells{scratchingHead = 0, shakingHands = 0, rapidBreathing = 0, , }; 
}

#endif /* PLAYER_H */