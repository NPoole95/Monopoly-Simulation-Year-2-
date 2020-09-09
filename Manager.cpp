#include "Manager.h"
#include "Definitions.h"
#include "boardPropertyFactory.h"
#include "Tile.h"
#include "Functions.h"
#include "Player.h"



bool doubleRent;
bool gameOver;

// method for reading in the monopoly board file
void CManager::ReadFile(const int NUMMAPSQUARES, tileList &boardTileList)
{
	ReadSeed(); // reads in the seeed and applies it to the random function

	ifstream fileInput; // ifstream for reading in files
	// variables used to store input data before passing int to a tile creation method
	int temp;			// temporary integer variable
	int cost;			// the cost of purchasing a tile
	int rent;			// the rent cost for landing on a tile
	string name;		// full name of a property
	string name1, name2, name3; // seperate strings for storing multiple words in one tile name (eg, "red" + "road" == "red road"
	ESquareGroup currentSquareGroup; // the group for a property (eg red or green)

	fileInput.open(MONOPOLYFILENAME); // opens the input file

	if (fileInput.is_open()) // Checks to see that the file has been opened sucessfully
	{
		for (int i = 0; i < NUMMAPSQUARES; i++) // runs through the whole file, based on the total number of squares on the board
		{
			fileInput >> temp; // reads in the tile code used to distinguish what type of tile is being read in (1-8)

			// this switch statements reads the first value of each line in the text file and assigns an appropriate property type
			switch (temp - ONE) // removes 1 from the variable to make it line up with the enum values which start at 0
			{
			case Property: // checks if the tile being created is a property
			{

				fileInput >> name1; // reads in the first word of the property name (eg red)
				fileInput >> name2; // reads in the second word of the property name (eg road)
									
				name = name1 + SPACE + name2; // combines these two name variables into one name

				fileInput >> cost; // reads in the propertys cost

				fileInput >> rent; // reads in the propertys rent

				fileInput >> temp; // reads in the propertys group

				switch (temp) // switch statement used to assign a propertys group based on the numebr read in from the file
				{
				case Red:  // checks if the property is red
					currentSquareGroup = Red; // sets the propertys group to red
					break;
				case Grey: // checks if the property is grey
					currentSquareGroup = Grey; // sets the propertys group to grey
					break;
				case Brown: // checks if the property is brown
					currentSquareGroup = Brown; // sets the propertys group to brown
					break;
				case Orange:// checks if the property is brown
					currentSquareGroup = Orange; // sets the propertys group to orange
					break;
				case Yellow:// checks if the property is yellow
					currentSquareGroup = Yellow; // sets the propertys group to yellow
					break;
				case Green:// checks if the property is green
					currentSquareGroup = Green; // sets the propertys group to green
					break;
				case Blue:// checks if the property is blue
					currentSquareGroup = Blue; // sets the propertys group to blue
					break;
				case Purple:// checks if the property is purple
					currentSquareGroup = Purple; // sets the propertys group to purple
					break;
				case NotProperty:// checks if the property is not in a group
					currentSquareGroup = NotProperty; // sets the propertys group to not a property
					break;
				}
				CProperty* ptr = new CProperty(); // creates a new property object
				ptr->SetValues(cost, rent, name, currentSquareGroup); // calls the function to initialize the property and its variables
				boardTileList.push_back(ptr); // pushes the new property onto the board deque
				break;
			}
			case Go: // checks if the tile being created is Go
			{
				fileInput >> name; // combines these two name variables into one name()

				CGo* ptr = new CGo;				// creates a new Go object
				ptr->SetValues(name);			// calls the function to initialize go and its variables
				boardTileList.push_back(ptr);	// pushes Go onto the board deque

				break;
			}
			case Airport: // checks if the tile being created is an airport 
			{
				fileInput >> name1;				// reads in the first word of the property name (eg red)
				fileInput >> name2;				// reads in the second word of the property name (eg road)
				cost = AIRPORTCOST;
				rent = AIRPORTRENT;
				name = name1 + SPACE + name2;	// combines these two name variables into one name

				CAirport* ptr = new CAirport();   // creates a new airport object
				ptr->SetValues(cost, rent, name); // calls the function to initialize the airport and its variables
				boardTileList.push_back(ptr);	  // pushes the new airport onto the board deque
				break;
			}
			case Bonus:  // checks if the tile being created is a bonus
			{
				fileInput >> name;			 // reads in files name
				CBonus* ptr = new CBonus();	 // creates a new bonus object
				ptr->SetValues(name);		 // calls the function to initialize the bonus and its variables
				boardTileList.push_back(ptr);// pushes the new bonus onto the board deque
				break;
			}
			case Penalty:  // checks if the tile being created is a penalty
			{
				fileInput >> name;				// reads in files name
				CPenalty* ptr = new CPenalty();	// creates a new penalty onject
				ptr->SetValues(name);			// calls the function to initialize the penalty and its variables
				boardTileList.push_back(ptr);	// pushes the new penalty onto the board deque
				break;
			}
			case Jail:  // checks if the tile being created is Jail
			{ 
				fileInput >> name;				// reads in files name
				CJail* ptr = new CJail();		// creates a new jail object
				ptr->SetValues(name);			// calls the function to initialize jail and its variables
				boardTileList.push_back(ptr);	// pushes jail onto the board deque
				break;
			}
			case GoToJail:  // checks if the tile being created is go to jail
			{
				fileInput >> name1;			// reads in the first word of the property name (eg go)
				fileInput >> name2;			// reads in the second word of the property name (eg to)
				fileInput >> name3;			// reads in the third word of the property name (eg jail)
				name = name1 + SPACE + name2 + SPACE + name3; // combines these two name variables into one name
				CGoToJail* ptr = new CGoToJail(); // creates a new go to jail object
				ptr->SetValues(name);			  // calls the function to initialize go to jail and its variables
				boardTileList.push_back(ptr);	  // pushes go to jail onto the board deque
				break;
			}
			case FreeParking:  // checks if the tile being created is free parking
			{
				fileInput >> name1;						// reads in the first word of the property name (eg red)
				fileInput >> name2;						// reads in the second word of the property name (eg road)
				name = name1 + SPACE + name2;			// combines these two name variables into one name
				CFreeParking* ptr = new CFreeParking(); // creates a new free parking object
				ptr->SetValues(name);					// calls the function to initialize free parking and its variables
				boardTileList.push_back(ptr);			// pushes free parking onto the board deque
				break;
			}
			}
		}
	}

}
// method for running a single player turn (called twice per game loop, once for each player)
void CManager::PlayerTurn(CPlayer *currentPlayer, CPlayer *opposingPlayer, int &roll, tileList &boardTileList)
{
	// roll dice
	roll = Random(); // calls the random function and stores the roll in thie int
	cout << currentPlayer->mName << ROLLS << roll << endl; // outputs a message showing what the player has rolled

	// advance on board
	for (int i = 0; i < roll; i++) // cycles through and moves the player one square at a time for the number of the roll
	{
		currentPlayer->mCurrentSquareValue = NextInArray(currentPlayer->mCurrentSquareValue, NUMMAPSQUARES); // increases the players board position by 1

		if (currentPlayer->mCurrentSquareValue == ZERO) // checks if the current square the player is on is Go
		{
			cout << currentPlayer->mName << PLAYERPASSEDGO << char(POUND) << PASSGOMONEY << endl; // outputs a message to show the player has passed go
			currentPlayer->mMoney += PASSGOMONEY;				   // adds the pass go money to the players money
		}
	}
	cout << currentPlayer->mName << LANDSON << boardTileList[currentPlayer->mCurrentSquareValue]->mTileName << endl; // outputs a message to show where the player has landed 

	// THE FOLLOWING VARIABLES AND FOR LOOP CONTROL RENT DOUBLING
	doubleRent = false; // sets the double rent controller to false, ready for the check
	ESquareGroup tileGroupChecker; // enum that stores the group of the property currently being checked by the for loop
	CPlayer* pTileOwnerChecker;	   // pointer that stores the owner of the property currently being checked by the for loop

	ESquareGroup TileGroup; // enum that stores the group of the property that the player has landed on
	CPlayer* pTileOwner;	// pointer that stores the owner of the property that the player landed on

	for (int i = 0; i < NUMMAPSQUARES; i++) // a for loop that runs through every property
	{
		tileGroupChecker = static_cast<CProperty*>(boardTileList[i])->mTileCurrentSquareGroup; // temporarily stores the group of the property currently being checked by the for loop
		pTileOwnerChecker = static_cast<CProperty*>(boardTileList[i])->pOwner;				   // temporarily stores the owner of the property currently being checked by the for loop

		TileGroup = static_cast<CProperty*>(boardTileList[currentPlayer->mCurrentSquareValue])->mTileCurrentSquareGroup; // temporarily stores the group of the property the player has landed on
		pTileOwner = static_cast<CProperty*>(boardTileList[currentPlayer->mCurrentSquareValue])->pOwner;				 // temporarily stores the owner of the property the player has landed on

		// this if statement causes the check to ignore go, jail, free parking and go to jail, as they can never have double rent 
		if (i != GOPOSITION && i != JAILPOSITION && i != FREEPARKINGPOSITION && i != GOTOJAILPOSITION)
		{
			if (tileGroupChecker == TileGroup && pTileOwnerChecker == pTileOwner && pTileOwner != nullptr) // checks if the colour of property the player has landed on, is the same as the tile currently being checked
			{																							   // also checks if the owner of the property is owned by the same person and that person isnt nobody
				doubleRent = true; // doubles the rent for this property
			}
			else if (tileGroupChecker == TileGroup) // else, if the properties are of the same colour, but not owned by the same person
			{
				doubleRent = false;	// does not double the rent for the property
				break; // breaks out of the for loop, as if one property is not owned by the same person, they cannot possibly own all of that group
			}
		}
	}

	// check the square that was landed on
	CheckSquare(currentPlayer->mCurrentSquareValue, currentPlayer, opposingPlayer, boardTileList);

	// MORTGAGES PROPERTIES
	if (currentPlayer->mMoney < ZERO)
	{
		for (int i = 0; i < NUMMAPSQUARES; i++) // a for loop that runs through every property
		{
			//tileGroupChecker = static_cast<CProperty*>(boardTileList[i])->mTileCurrentSquareGroup; // temporarily stores the group of the property currently being checked by the for loop
			pTileOwnerChecker = static_cast<CProperty*>(boardTileList[i])->pOwner;				   // temporarily stores the owner of the property currently being checked by the for loop

			if (pTileOwnerChecker == currentPlayer) // checks if the player owns the current property being checked
			{
				static_cast<CProperty*>(boardTileList[i])->mMortgaged = true; // sets the current property to mortgaged, disabling the rent paying option
				currentPlayer->mMoney += static_cast<CProperty*>(boardTileList[i])->mTileCost; // adds the value of the property to the players money
				cout << currentPlayer->mName << MORTGAGED << boardTileList[i]->mTileName << FOR << char(POUND) << static_cast<CProperty*>(boardTileList[i])->mTileCost << endl; // outputs a message showing a property has been mortgaged and how much the player recieved
			}
			if (currentPlayer->mMoney > ZERO) // checks if the players money is positive, meaning no more properties need to be mortgaged
			{
				break; // breaks out of the for loop stopping any more properties being mortgaged unnecessarily
			}
		}
	}
	if (currentPlayer->mMoney < ZERO) // checks if the player still has no money after mortgaging all available properties
	{
		cout << GAMEOVER << endl; // outputs a message showing the game is over
		cout << currentPlayer->mName << NOPROPERTIES << endl; // explains that the player has no properties left to mortgage
		gameOver = true; // sets the game over boolean to true
	}

	// UNMORTGAGES PROPERTIES

	if (currentPlayer->mMoney > ZERO)
	{
		for (int i = 0; i < NUMMAPSQUARES; i++) // a for loop that runs through every property
		{
			//tileGroupChecker = static_cast<CProperty*>(boardTileList[i])->mTileCurrentSquareGroup; // temporarily stores the group of the property currently being checked by the for loop
			pTileOwnerChecker = static_cast<CProperty*>(boardTileList[i])->pOwner;				   // temporarily stores the owner of the property currently being checked by the for loop

			if (pTileOwnerChecker == currentPlayer && currentPlayer->mMoney > static_cast<CProperty*>(boardTileList[i])->mTileCost && static_cast<CProperty*>(boardTileList[i])->mMortgaged == true)
			{
				static_cast<CProperty*>(boardTileList[i])->mMortgaged = false; // sets the current property to no longer be mortgaged, re enabline the rent paying option
				currentPlayer->mMoney -= static_cast<CProperty*>(boardTileList[i])->mTileCost; // removes the cost of the property from the players money
				cout << currentPlayer->mName << UNMORTGAGED << boardTileList[i]->mTileName << FOR << char(POUND) << static_cast<CProperty*>(boardTileList[i])->mTileCost << endl; // outputs a message showing that the property has been unmortgaged
			}
		}
	}


	// end the players turn
	cout << currentPlayer->mName << HAS << char(POUND) << currentPlayer->mMoney << endl; // outputs a message showing the players new money total
}

// method that checks the square landed on by a player
void CManager::CheckSquare(int currentSquareValue, CPlayer *currentPlayer, CPlayer *opposingPlayer, tileList &boardTileList)
{
	boardTileList[currentPlayer->mCurrentSquareValue]->CreateTile(currentPlayer, opposingPlayer); // calls a method for the tile that was landed on and runs the appropriate function
}

// method that creates an obkect of the player class
void CManager::PlayerCreate(CPlayer *playerName, string playerNameString)
{
	playerName->mName = playerNameString;	// assigns the players name to the variable that was passed as a parameter
	playerName->mMoney = PLAYERSTARTINGMONEY;// sets the players money to the starting amount held in definitions.h
	playerName->mCurrentSquareValue = ZERO;	// sets the players starting position to 0 (GO)
	playerName->mInJail = false;				// sets the player to be not currently in jail
}

// method that starts the game
void CManager::GameStart()
{
	roll = ZERO; // initializes the roll to 0, as no player has rolled yet
	

	PlayerCreate(&dog, DOGNAME); // calls the player create method and initializes all of the players variables
	PlayerCreate(&car, CARNAME); // calls the player create method and initializes all of the players variables

	ReadFile(NUMMAPSQUARES, boardTileList); // reads in the map file and creates the monopoly board deque

	cout << WELCOMETOMONOPOLY << endl << endl; // outputs a welcome message

	//for (int roundCounter = 0; roundCounter < NUMROUNDS; roundCounter++) // the game loop
	//{
	//	
	//	PlayerTurn(&dog, &car, roll, boardTileList); // calls the player turn function for Dogs turn
	//	
	//	if (gameOver == true) // checks if the game over bool has been set to true, meaning a player has negative money and no properties left to mortgage
	//	{
	//		break; // breaks out of the game loop
	//	}
	//	
	//	PlayerTurn(&car, &dog, roll, boardTileList); // calls the player turn function for Cars turn
	//	
	//	if (gameOver == true) // checks if the game over bool has been set to true, meaning a player has negative money and no properties left to mortgage
	//	{
	//		break; // breaks out of the game loop
	//	}
	//	
	//	cout << endl; // outputs an end line to seperate different turns in the console
	//}
}