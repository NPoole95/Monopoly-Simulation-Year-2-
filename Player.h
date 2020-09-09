#pragma once
#include "Definitions.h"
// Player class definition

class CPlayer
{
public:
	void SetValues(int cost, int rent, std::string name); // method that initializes all of the players variables fopr the start of the game

	std::string mName;		// players name
	int mMoney;				// players current money
	int mCurrentSquareValue;	// the players current location on the board. this int cycles between 0 and 26 using the next in array function
	bool mInJail;			// a boolean that knows if the player is currently in jail
	std::string mTileEffectMessage; // the message output to the screen if there is an effect when the player lands on a tile (e.g. paying rent)

protected:
	
};

