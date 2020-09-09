// Implementation of Player Class
#pragma once
#include "Player.h"

void CPlayer::SetValues(int cost, int rent, std::string name) // method that initializes all of the players variables fopr the start of the game
{
	mName = name;					// sets the players name to the string that was passed to the method
	mMoney = PLAYERSTARTINGMONEY;	// initialkizes teh players money to the starting amount
	mCurrentSquareValue = ZERO;		// sets the players position on the board to 0 (GO)
	mInJail = false;					// sets the player to not currently be in jail
	mTileEffectMessage = " ";
};
