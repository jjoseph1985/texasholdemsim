#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <math>
#include <string>
#include "tells.h"

class Player : public Tells
{
	public:
		string firstName = "";
		string lastName = "";

		int skillLevel = 0;

		enum tells{scratchingHead=0, shakingHands=0, rapidBreathing=0};
}

#endif /* PLAYER_H */