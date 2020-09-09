#pragma once
#include "boardProperty.h"       // Base class definition
#include "Player.h"				 // player class definition
#include "Definitions.h"

// Airport class definition
class CAirport : public CBoardTile
{
public:

	bool mMortgaged;

	void SetValues(int cost, int rent, string name); // method that initialises the variables of an airport as it is loaded by the read map function
	void BuyProperty(CPlayer *currentPlayer); // method for when a player purchases an airport	
	void PayRent(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method for a player paying rent on an airport

protected:
	int mTileCost; // the cost of buying an airport
	int mTileRent; // the rent payed when landing on an owned airport

	CPlayer* pOwner; // a pointer to a player object which represents who owns it. if this pointer appears as null, nobody owns the property
	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method declaration for when a player lands on an airport.

};

// Bonus class definition
class CBonus : public CBoardTile 
{
public:
	void SetValues(string name); // method that initialises the variables of a bonus as it is loaded by the read map function

protected:

	// Creates a property with this type
	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method declaration for when a player lands on an bonus.
	int mBonusRoll;			// integer that stores the players roll when they land on a bonus square, determining which bonus the recieve
	string mBonusMessage;	// string that stores the appropriate bonus message based on the roll
	int mBonusMoney;			// int that stores the appropriate bonus money based on the roll

};

// FreeParking class definition
class CFreeParking : public CBoardTile 
{

public:
	void SetValues(string name); // method that initialises the variables of free parking as it is loaded by the read map function

protected:

	// Creates a property with this type
	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method declaration for when a player lands on free parking.
};

// Go class definition
class CGo : public CBoardTile 
{
public:
	void SetValues(string name); // method that initialises the variables of GO as it is loaded by the read map function
	
protected:
	int mTilePassGoMoney; // integer that holds the reward for a player passing go

	// Creates a property with this type
	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method declaration for when a player lands on Go.
};

// GoToJail class definition
class CGoToJail : public CBoardTile 
{
public:
	void SetValues(string name); // method that initialises the variables of go to jail as it is loaded by the read map function
	void SentToJail(CPlayer *currentPlayer);	// method for when a player is sent to jail

protected:
	int mTileBailMoney;		// integer storing the cost of bail
	string mTileJailMessage;	//  string storing the message showing a player was sent to jail

	// Creates a property with this type
	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method declaration for when a player lands on Go to jail.
};

// Jail class definition
class CJail : public CBoardTile 
{
public:
	void SetValues(string name); // method that initialises the variables of jail as it is loaded by the read map function

protected:
	// Creates a property with this type
	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method declaration for when a player lands on jail.
};

// Penalty class definition
class CPenalty : public CBoardTile  
{
public:
	void SetValues(string name); // method that initialises the variables of a penalty as it is loaded by the read map function

protected:

	// Creates a property with this type
	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // method declaration for when a player lands on a penalty.
	
	int mPenaltyRoll;		// integer that stores the players roll when they land on a penalty square, determining which penalty they recieve
	string mPenaltyMessage;	// string that stores the appropriate penalty message based on the roll
	int mPenaltyMoney;		// int that stores the appropriate penalty money based on the roll
};

// Property class definition
class CProperty : public CBoardTile  
{
public:

	void SetValues(int cost, int rent, string name, ESquareGroup currentSquareGroup); // method that initialises the variables of a property as it is loaded by the read map function

	bool mMortgaged;
	ESquareGroup mTileCurrentSquareGroup; // enum that stors the group of the property
	CPlayer* pOwner;	// pointer to a player object that shows who owns it
	int mTileCost;	// integer that stores the cost of the property
	int mTileRent;	// integer that stors the rent of the property

protected:

	void CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer); // Creates a property with this type
	void BuyProperty(CPlayer *currentPlayer);						  // method for a player buying a property
	void PayRent(CPlayer *currentPlayer, CPlayer *opposingPlayer);	  // method for a player paying rent on a property
	

};

using tileList = deque<CBoardTile*>;  // typedef for the monopoly board deque to clear up ugly syntax
