#ifndef TELLS_H
#define TELLS_H

#include <vector>
#include <math>
#include <string>

abstract class Tells
{
	public:
		enum Tells{ scratchHead, shakingHands, rapidBreathing };

	private:
		int getTell(/*INPUT STUFF HERE!*/);
		setTell(/*INPUT STUFF HERE!*/);
}

#endif /* TELLS_H */