#pragma once

#include "Definitions.h" // type definitions
#include "Player.h"

// CBoardTile class - cannot be instantiated

class CBoardTile
{
public:
	// Interfaces don't need a constructor (cannot be instantiated anyway)
	// They DO need a virtual destructor 

	virtual ~CBoardTile() {};

	std::string mTileName;
	// Pure Virtual function to be implemented in derived class.

	virtual void CreateTile(CPlayer* currentPlayer, CPlayer* opposingPlayer) = 0;

};
