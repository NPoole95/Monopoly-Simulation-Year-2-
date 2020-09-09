#pragma once
#include "Definitions.h"
#include "tile.h"

// manager class declaration
class CManager
{
public:
	CManager() {};  // constructor for the manager class
	~CManager() {}; // destructor for the manager class
	void ReadFile(const int NUMMAPSQUARES, tileList &boardTileList);													// declaration for the red file method
	void PlayerTurn(CPlayer *currentPlayer, CPlayer *opposingPlayer, int &roll, tileList &boardTileList);				// declaration for the player turn method
	void CheckSquare(int currentSquareValue, CPlayer *currentPlayer, CPlayer *opposingPlayer, tileList &boardTileList);	// declaration for the check square method
	void PlayerCreate(CPlayer *playerName, string playerNameString);													// declaration for the player create method
	void GameStart();													
	
	CPlayer dog; // creates an objext of the player class for Dog (player 1)
	CPlayer car; // creates an objext of the player class for Car (player 2)// declaration for the game start method
	int roll;
	tileList boardTileList; // declares the deque storing all of the tiles on the board
private:

};