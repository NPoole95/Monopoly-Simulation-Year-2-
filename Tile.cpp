#pragma once
#include "Tile.h"
#include "Functions.h"
#include "Player.h"

// Implementation of property class for Airport
//
// Method that runs when a player lands on an airport
void CAirport::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	if (pOwner == nullptr) // Checks if the airport is not owned by anybody
	{
		BuyProperty(currentPlayer); // calls the buy airport method
	}
	else if (pOwner == opposingPlayer) // checks if the airport is owned by the opposing player
	{
		PayRent(currentPlayer, opposingPlayer); // calls the pay rent method
	}
	else if (pOwner == currentPlayer) // checks if the airport is owned by the current player
	{
		cout << currentPlayer->mName << OWNS << mTileName << endl; // outputs a message showing that the player already owns this tile
		currentPlayer->mTileEffectMessage = OWNS + mTileName;
	}
	// if the property is already owned by the player, nothing happens
}

void CAirport::SetValues(int cost, int rent, string name) // method that initialises the variables of an airport as it is loaded by the read map function
{
	mTileCost = cost; // initialises the tiles cost variable to that which was passed to the method as a parameter
	mTileRent = rent; // initialises the tiles rent variable to that which was passed to the method as a parameter
	mTileName = name; // initialises the tiles name to that which was passed to the method as a parameter
	pOwner = nullptr; // initialises the tiles owner to null, meaning that nobody currently owns it
};

void CAirport::BuyProperty(CPlayer *currentPlayer) // method for when a player purchases an airport
{
	pOwner = currentPlayer;				// sets the pointer in the airport object to the current player object
	currentPlayer->mMoney -= mTileCost;	// removes the cost of the current airport from the current players money
	cout << currentPlayer->mName << BUYS << mTileName << FOR << char(POUND) << mTileCost << endl; // outputs a message showing which player has bought which airport for what amount
	currentPlayer->mTileEffectMessage = BUYS + mTileName + FOR + "£" + to_string(mTileCost);
};
void CAirport::PayRent(CPlayer *currentPlayer, CPlayer *opposingPlayer) // method for a player paying rent on an airport
{
	currentPlayer->mMoney -= mTileRent;	// removes the rent of the airport from the current players money
	opposingPlayer->mMoney += mTileRent;  // adds this money to the opposing players money
	cout << currentPlayer->mName << PAYS << char(POUND) << mTileRent << endl; // outputs a message showing which player paid rent for what amount
	currentPlayer->mTileEffectMessage = PAYS + "£" + to_string(mTileRent);
};

// Implementation of property class for Bonus
//
// Method that runs when a player lands on a bonus
void CBonus::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	mBonusRoll = Random(); // rolls to determine which bonus the player will recieve

	switch (mBonusRoll) // runs a switch statement based on the roll
	{
	case ONE: // checks if the player rolled a 1
		mBonusMessage = BONUSMESSAGE20; // sets the output message for the bonus
		mBonusMoney = BONUSMONEY20;	   // sets the bonus money to be recieved
		break;
	case TWO: // checks if the player rolled a 2
		mBonusMessage = BONUSMESSAGE50; // sets the output message for the bonus
		mBonusMoney = BONUSMONEY50;	   // sets the bonus money to be recieved
		break;
	case THREE:// checks if the player rolled a 3
		mBonusMessage = BONUSMESSAGE100; // sets the output message for the bonus
		mBonusMoney = BONUSMONEY100;		// sets the bonus money to be recieved
		break;
	case FOUR: // checks if the player rolled a 4
		mBonusMessage = BONUSMESSAGE150; // sets the output message for the bonus
		mBonusMoney = BONUSMONEY150;		// sets the bonus money to be recieved
		break;
	case FIVE: // checks if the player rolled a 5
		mBonusMessage = BONUSMESSAGE200; // sets the output message for the bonus
		mBonusMoney = BONUSMONEY200;		// sets the bonus money to be recieved
		break;
	case SIX: // checks if the player rolled a 6
		mBonusMessage = BONUSMESSAGE300; // sets the output message for the bonus
		mBonusMoney = BONUSMONEY300;		// sets the bonus money to be recieved
		break;
	}
	currentPlayer->mMoney += mBonusMoney; // increases the players money by the amount of bonus money recieved
	cout << mBonusMessage << SPACE << currentPlayer->mName << GAINS << char(POUND) << mBonusMoney << endl; // outputs a message to show the player recieved bonus money
	currentPlayer->mTileEffectMessage = mBonusMessage + SPACE + currentPlayer->mName + GAINS + "£" + mBonusMessage;
}
void CBonus::SetValues(string name) // method that initialises the variables of a bonus as it is loaded by the read map function
{
	mTileName = name; // initialises the tiles name to that which was passed to the method as a parameter
};

// Implementation of property class for Free Parking
//
// Method that runs when a player lands on free parking
void CFreeParking::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	cout << currentPlayer->mName << ISRESTING << endl; // outputs a message to show the player is just resting
	currentPlayer->mTileEffectMessage = ISRESTING;
}
void CFreeParking::SetValues(string name) // method that initialises the variables of free parking as it is loaded by the read map function
{
	mTileName = name; // initialises the tiles name to that which was passed to the method as a parameter
};
// Implementation of property class for Go
//
// Method that runs when a player lands on Go
void CGo::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{

}
void CGo::SetValues(string name) // method that initialises the variables of GO as it is loaded by the read map function
{
	mTilePassGoMoney = PASSGOMONEY; // sets the pass go tiles money variable to the amount stored in the constant in definitions.h
	mTileName = name; // initialises the tiles name to that which was passed to the method as a parameter
};

// Implementation of property class for Go To Jail
//
// Method that runs when a player lands on Go to jail
void CGoToJail::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	SentToJail(currentPlayer); // calls the send to jail method, sending the player to jail
}

void CGoToJail::SetValues(string name) // method that initialises the variables of go to jail as it is loaded by the read map function
{
	mTileJailMessage = TOJAILMESSAGE;	// sets the go to jail message to the one stored in definitions.h
	mTileBailMoney = BAILMONEY;			// sets the bail money to the value stored in definitions.h
	mTileName = name;					// initialises the tiles name to that which was passed to the method as a parameter
};

void CGoToJail::SentToJail(CPlayer *currentPlayer)	// method for when a player is sent to jail
{
	currentPlayer->mCurrentSquareValue = SIX;	// moves the player to tile 6 on the board (jail)
	currentPlayer->mMoney -= mTileBailMoney;		// removes the bail money from the players current money
													//currentPlayer->inJail = true;				// sets the player to be in jail
	cout << mTileJailMessage << endl;
	cout << currentPlayer->mName << GOESTOJAIL << endl; // outputs a message showing the player has gone to jail
	cout << currentPlayer->mName << PAYS << char(POUND) << BAILMONEY << endl; // outputs a message showing a player has paid bail

	currentPlayer->mTileEffectMessage = GOESTOJAIL + PAYS + "£" + to_string(BAILMONEY);
}

// Implementation of property class for Jail
//
// Method that runs when a player lands on jail
void CJail::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	cout << currentPlayer->mName << ISJUSTVISITING << endl; // outputs a message to show the player is just visiting jail
	currentPlayer->mTileEffectMessage = ISJUSTVISITING;
}

void CJail::SetValues(string name) // method that initialises the variables of jail as it is loaded by the read map function
{
	mTileName = name; // initialises the tiles name to that which was passed to the method as a parameter
};

// Implementation of property class for Penalty
//
// Method that runs when a player lands on penalty
void CPenalty::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	mPenaltyRoll = Random(); // rolls to determine which penalty the player will recieve

	switch (mPenaltyRoll) // runs a switch statement based on the roll
	{
	case ONE: // checks if the player rolled a 1
		mPenaltyMessage = PENALTYMESSAGE20; // sets the output message for the penalty
		mPenaltyMoney = PENALTYMONEY20;	   // sets the penalty money to be deducted
		break;
	case TWO: // checks if the player rolled a 2
		mPenaltyMessage = PENALTYMESSAGE50; // sets the output message for the penalty
		mPenaltyMoney = PENALTYMONEY50;	   // sets the penalty money to be deducted
		break;
	case THREE: // checks if the player rolled a 3
		mPenaltyMessage = PENALTYMESSAGE100; // sets the output message for the penalty
		mPenaltyMoney = PENALTYMONEY100;		// sets the penalty money to be deducted
		break;
	case FOUR: // checks if the player rolled a 4
		mPenaltyMessage = PENALTYMESSAGE150; // sets the output message for the penalty
		mPenaltyMoney = PENALTYMONEY150;		// sets the penalty money to be deducted
		break;
	case FIVE: // checks if the player rolled a 5
		mPenaltyMessage = PENALTYMESSAGE200; // sets the output message for the penalty
		mPenaltyMoney = PENALTYMONEY200;		// sets the penalty money to be deducted
		break;
	case SIX: // checks if the player rolled a 6
		mPenaltyMessage = PENALTYMESSAGE300; // sets the output message for the penalty
		mPenaltyMoney = PENALTYMONEY300;		// sets the penalty money to be deducted
		break;
	}

	currentPlayer->mMoney -= mPenaltyMoney;  // decreases the players money by the amount of penalty money lost
	cout << mPenaltyMessage << SPACE << currentPlayer->mName << LOSES << mPenaltyMoney << endl; // outputs a message to show the player lost penalty money
	currentPlayer->mTileEffectMessage = mPenaltyMessage + SPACE + currentPlayer->mName + LOSES + to_string(mPenaltyMoney);

}

void CPenalty::SetValues(string name) // method that initialises the variables of a penalty as it is loaded by the read map function
{
	mTileName = name; // initialises the tiles name to that which was passed to the method as a parameter
};

// Implementation of property class for Property
//
// Method that runs when a player lands on a property
void CProperty::CreateTile(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	if (pOwner == nullptr && currentPlayer->mMoney > ZERO) // checks if nobody owns the property
	{
		BuyProperty(currentPlayer); // calls the buy property method
	}
	else if (pOwner == opposingPlayer)  // checks if the property is owned by the opposing player
	{
		PayRent(currentPlayer, opposingPlayer); // calls the pay rent method
	}
	else if (pOwner == currentPlayer) // checks if the airport is owned by the current player
	{
		cout << currentPlayer->mName << OWNS << mTileName << endl; // outputs a message showing that the player already owns this tile
		currentPlayer->mTileEffectMessage = currentPlayer->mName + OWNS + mTileName;
	}
}

void CProperty::BuyProperty(CPlayer *currentPlayer) // method for a player buying a property
{
	pOwner = currentPlayer;				// sets the owner of the property to the current player
	currentPlayer->mMoney -= mTileCost;	// removes teh cost of the property from the players money
	cout << currentPlayer->mName << BUYS << mTileName << FOR << char(POUND) << mTileCost << endl; // outputs a message showing which player has bought which property for what amount
	currentPlayer->mTileEffectMessage = currentPlayer->mName + BUYS + mTileName + FOR + "£" + to_string(mTileCost);
};

void CProperty::PayRent(CPlayer *currentPlayer, CPlayer *opposingPlayer)
{
	if (mMortgaged == false)
	{
		if (doubleRent == true)
		{
			currentPlayer->mMoney -= (mTileRent * TWO);	// removes the rent of the propertyy from the current players money
			opposingPlayer->mMoney += (mTileRent * TWO);	// adds this money to the opposing players money
			cout << currentPlayer->mName << PAYS << char(POUND) << (mTileRent * TWO) << endl;	// outputs a message showing which player paid rent for what amount
			currentPlayer->mTileEffectMessage = currentPlayer->mName + PAYS + "£" + to_string(mTileRent * TWO);
		}
		else
		{
			currentPlayer->mMoney -= mTileRent;	// removes the rent of the propertyy from the current players money
			opposingPlayer->mMoney += mTileRent;	// adds this money to the opposing players money
			cout << currentPlayer->mName << PAYS << char(POUND) << mTileRent << endl;	// outputs a message showing which player paid rent for what amount
			currentPlayer->mTileEffectMessage = currentPlayer->mName + PAYS + "£" + to_string(mTileRent);
		}
	}
}

void CProperty::SetValues(int cost, int rent, string name, ESquareGroup currentSquareGroup) // method that initialises the variables of a property as it is loaded by the read map function
{
	mTileCost = cost; 	// initialises the tiles cost variable to that which was passed to the method as a parameter
	mTileRent = rent;	// initialises the tiles rent variable to that which was passed to the method as a parameter
	mTileCurrentSquareGroup = currentSquareGroup; // initializes the propertys group enum (eg red) to that which was passed to the method as a parameter													  
	mTileName = name; // initialises the tiles name to that which was passed to the method as a parameter	   
	pOwner = nullptr; // initialises the tiles owner to null, meaning that nobody currently owns it

};