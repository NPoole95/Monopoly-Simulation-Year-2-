#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <memory>

using namespace std;

// enum containing the different property groups
enum ESquareGroup { Red, Grey, Brown, Orange, Yellow, Green, Blue, Purple, NotProperty };

extern bool doubleRent; // A boolean value used to control the doubling of rent
extern bool gameOver;   // used to tell if the game has ended

// constants that holds the quantities of different things
const int NUMMAPSQUARES = 26;  // number of tiles on the board
const int NUMPENALTIES = 6;    // number of penalty cards
const int NUMBONUSES = 6;	   // number of bonus cards
const int NUMROUNDS = 20;	   // number of rounds in the game
const float MAXTURNTIMER = 2.0f; // the amount of time between each players turn
const int JAILSQNUMBER = 6;	   // the location of the jail square on the baord

const int RESOLUTIONWIDTH = 1920;
const int RESOLUTIONHEIGHT = 1080;

const char POUND = 156;		   // ascii value of the pound sign (£) used for output 

// constants that hold values of fees or rents
const int AIRPORTCOST = 200;   // the cost of an airport
const int AIRPORTRENT = 10;	   // the rent for an airport
const int BAILMONEY = 50;	   // the bail money for leaving jail		   

// numbers for potential dice rolls and also 0 
const int ZERO = 0;
const int ONE = 1;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const int FIVE = 5;
const int SIX = 6;

// locations of notable properties on the board

const int GOPOSITION = 0;
const int JAILPOSITION = 6;
const int FREEPARKINGPOSITION = 13;
const int GOTOJAILPOSITION = 19;

// constants for initializing the player class
const int PLAYERSTARTINGMONEY = 1500; // the money the player starts the game with
const int PASSGOMONEY = 200;		  // the money earned when a player passes go


// constants storing strings for console output
const string TOJAILMESSAGE = "You have been sent to jail";  // when the player is sent to jail
const string GOESTOJAIL = " goes to jail";					// when the player moves to the jail tile
const string BUYS = " buys ";								// when the player buys a property
const string PAYS = " pays ";								// then the player pays a fee
const string FOR = " for ";									// when displaying the amount a player pays
const string MONOPOLYFILENAME = "Monopoly.txt";				// the file storing all of the monopoly board data
const string SEEDFILENAME = "seed.txt";						// the file storing the seed for the rand function
const string SPACE = " ";									// a space
const string ROLLS = " rolls ";								// when a player rolls the dice
const string PLAYERPASSEDGO = " has passed go and collects ";// when a player passes go
const string LANDSON = " lands on ";						// when a player lands on a property
const string HAS = " has ";									// when displaying a players money
const string DOGNAME = "Dog";								// dog players name
const string CARNAME = "Car";								// car players name
const string WELCOMETOMONOPOLY = "Welcome to Monopoly";		// monopoly welcome message
const string ISJUSTVISITING = " is just visiting";			// when a player lands on the jail tile, but is not in jail
const string ISRESTING = " is resting";						// when a player lands on free parking
const string MORTGAGED = " mortgaged ";						// when a player mortgages a property
const string UNMORTGAGED = " unmortgaged ";					// when a player unmortgages a property
const string OWNS = " owns ";								// when a player already owns the property they landed on
const string GAMEOVER = "Game over.";									// a message to show the game is over	
const string NOPROPERTIES = " has no properties left to mortgage.";							// a message showing that a player has no properties left to mortgage

const string GAINS = " gains ";								// used when displaying a players bonus win
const string BONUSMESSAGE20 = "Find some money";			// player finds some money (20)
const int BONUSMONEY20 = 20;								// bonus money of 20
const string BONUSMESSAGE50 = "Win competition";			// player wins a competition (50)
const int BONUSMONEY50 = 50;								// bonus money of 50
const string BONUSMESSAGE100 = "Tax rebate";				// player gets a tax rebate (100)
const int BONUSMONEY100 = 100;								// bonus money of 100
const string BONUSMESSAGE150 = "Win lottery";				// player wins the lottery (150)
const int BONUSMONEY150 = 150;								// bonus money of 150
const string BONUSMESSAGE200 = "Bequest";					// player gets a bequest (200)
const int BONUSMONEY200 = 200;								// bonus money of 200
const string BONUSMESSAGE300 = "Birthday";					// players birthday (300)
const int BONUSMONEY300 = 300;								// bonus money of 300

const string LOSES = " loses ";								// used when displaying a players penalty loss
const string PENALTYMESSAGE20 = "Pay food bill";			// player has to pay food bill (20)
const int PENALTYMONEY20 = 20;								// penalty money of 20
const string PENALTYMESSAGE50 = "Pay phone bill";			// player has to pay phone bill (50)
const int PENALTYMONEY50 = 50;								// penalty money of 50
const string PENALTYMESSAGE100 = "Pay heating bill";		// player has to pay heating bill (100)
const int PENALTYMONEY100 = 100;							// penalty money of 100
const string PENALTYMESSAGE150 = "Pay vehicle tax";			// player has to pay vehicle tax (150)
const int PENALTYMONEY150 = 150;							// penalty money of 150
const string PENALTYMESSAGE200 = "Pay fuel bill";			// player has to pay fuel bill (200)
const int PENALTYMONEY200 = 200;							// penalty money of 200
const string PENALTYMESSAGE300 = "Pay windfall tax";		// player has to pay windfall tax (300)
const int PENALTYMONEY300 = 300;							// penalty money of 300