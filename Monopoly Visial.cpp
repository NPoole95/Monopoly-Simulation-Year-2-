// Monopoly Visial.cpp: A program using the TL-Engine

#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "stdafx.h"
#include "Functions.h"
#include "boardProperty.h"
#include "boardPropertyFactory.h"
#include "Manager.h"
#include "Tile.h"
#include <sstream>
using namespace tle;
using namespace std;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed(RESOLUTIONWIDTH, RESOLUTIONHEIGHT);

	float frameTime = 1.0f;

	ICamera* myCamera;															// Creates the camera
	myCamera = myEngine->CreateCamera(kManual);

	myCamera->Move(17.5, 30, 45);												// moves the camera back into third person view
	myCamera->RotateX(90);														// rotates the gamera 20 degrees to look down


	// Add default folder for meshes and other media
	//myEngine->AddMediaFolder( "./Media" );
	myEngine->AddMediaFolder("C:\\Users\\nicho\\Desktop\\Uni work\\Year 2\\monopoly with visual attempt\\Monopoly Visial\\Media");

	const int kNumTiles = 26;
	const float spriteXPosition[kNumTiles] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 35.0f,
										35.0f, 35.0f, 35.0f, 35.0f, 35.0f, 35.0f, 30.0f, 25.0f, 20.0f, 15.0f, 10.0f, 5.0f};
	const float spriteYPosition = 0.0f;
	const float spriteZPosition[kNumTiles] = {0.0f, 5.0f, 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 
										30.0f, 25.0f, 20.0f, 15.0f, 10.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	const float spriteRotation[kNumTiles] = { 270.0f, -90.0f, -90.0f, -90.0f, -90.0f, -90.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
										90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f };
	const string tileSkinName[kNumTiles] = {"Go.png", "RedRoad.png", "RedStreet.png", "Bonus.png", "GreyRoad.png", "GreyStreet.png", "Jail.png", "BrownRoad.png", "BrownStreet.png", "SpeedyAirport.png",
									  "OrangeRoad.png", "OrangeStreet.png", "OrangeWay.png", "FreeParking.png", "YellowRoad.png", "YellowStreet.png", "Penalty.png", "GreenRoad.png", "GreenStreet.png", 
									  "GoToJail.png", "BlueRoad.png", "BlueStreet.png", "BlueWay.png", "ShuttleAirport.png", "PurpleRoad.png", "PurpleStreet.png", };
	const float playerYPosition = spriteYPosition + 3.0f;

	const float dogOffset = 1.5f; // value to make sure the car and dog models are not on top of each other
	float turnTimer = 0.0f;
	bool dogsTurn = true; // a bolean to switch between the two players turns

	IMesh* quadMesh = myEngine->LoadMesh("quad.x");
	IMesh* cubeMesh = myEngine->LoadMesh("Cube.x");

	IModel* boardTiles[kNumTiles];
	IModel* carModel = cubeMesh->CreateModel(spriteXPosition[0], playerYPosition, spriteZPosition[0]);
	IModel* dogModel = cubeMesh->CreateModel(spriteXPosition[0] + dogOffset, playerYPosition, spriteZPosition[0] + dogOffset);

	carModel->SetSkin("blue.png");
	dogModel->SetSkin("green.png");
	carModel->Scale(0.1f);
	dogModel->Scale(0.1f);

	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36); // Declares the font and font size used when outputting text
	bool passedGo = false;
	stringstream playerMoneyText;
	stringstream rollText;   // screen dice roll output
	stringstream landsOnText; // output for what tile the players are currently on
	stringstream passedGoText; // output for what tile the players are currently on
	stringstream tileEffectText; // output the effect of a time (eg paying rent)

	for (int i = 0; i < kNumTiles; ++i)
	{
		boardTiles[i] = quadMesh->CreateModel(spriteXPosition[i], spriteYPosition, spriteZPosition[i]);
		boardTiles[i]->SetSkin(tileSkinName[i]);
		boardTiles[i]->RotateX(90);
		boardTiles[i]->Scale(0.5f);
		
		boardTiles[i]->RotateY(spriteRotation[i]);
	}
	
	/**** Set up your scene here ****/
	CManager game; // creates an object of the game manager class

	game.GameStart(); // calls the game start method

	int roundCounter = 0;
	float rotationValue = 0;

	myEngine->Timer(); // calls the timer used for frame time

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		frameTime = myEngine->Timer(); // updates frame time 
		turnTimer -= frameTime;

		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}

		// run the players turn
		//for (int roundCounter = 0; roundCounter < NUMROUNDS; roundCounter++) // the game loop
		if(roundCounter < NUMROUNDS && turnTimer <= 0.0f)
		{
			if (dogsTurn)
			{
				game.dog.mTileEffectMessage = "";
				game.PlayerTurn(&game.dog, &game.car, game.roll, game.boardTileList); // calls the player turn function for Dogs turn

				if (gameOver == true) // checks if the game over bool has been set to true, meaning a player has negative money and no properties left to mortgage
				{
					break; // breaks out of the game loop
				}
				dogsTurn = !dogsTurn;
				turnTimer = MAXTURNTIMER;
			}
			else
			{
				game.car.mTileEffectMessage = "";
				game.PlayerTurn(&game.car, &game.dog, game.roll, game.boardTileList); // calls the player turn function for Cars turn

				if (gameOver == true) // checks if the game over bool has been set to true, meaning a player has negative money and no properties left to mortgage
				{
					break; // breaks out of the game loop
				}
				dogsTurn = !dogsTurn;
				turnTimer = MAXTURNTIMER;
			}


			roundCounter++;
			cout << endl; // outputs an end line to seperate different turns in the console
		}
		// update the onscreen text
		if (dogsTurn) // output the cars info on screen here instead because the game immidiately switches to the dogs turn the moment it is processed
		{
			rollText << "Car rolls: " << game.roll; // outputs the current roll
			landsOnText << "Car" << LANDSON << game.boardTileList[game.car.mCurrentSquareValue]->mTileName << endl; // outputs a message to show where the player has landed
			tileEffectText << game.car.mTileEffectMessage;
			if (game.roll > game.car.mCurrentSquareValue)
			{
				passedGo = true;
				landsOnText << "Car " << PLAYERPASSEDGO << char(POUND) << PASSGOMONEY << endl; // outputs a message to show the player passed go
			}
			else
			{
				passedGo = false;
			}
		}
		else
		{
			rollText << "Dog rolls: " << game.roll; // outputs the current roll
			landsOnText << "Dog" << LANDSON << game.boardTileList[game.dog.mCurrentSquareValue]->mTileName << endl; // outputs a message to show where the player has landed 
			tileEffectText << game.dog.mTileEffectMessage;
			if (game.roll > game.dog.mCurrentSquareValue)
			{
				passedGo = true;
				landsOnText << "Dog " << PLAYERPASSEDGO << char(POUND) << PASSGOMONEY << endl; // outputs a message to show the player passed go
			}
			else
			{
				passedGo = false;
			}
		}

		playerMoneyText << "Car has: £" << game.car.mMoney << " Dog has: £" << game.dog.mMoney;

		myFont->Draw(playerMoneyText.str(), (RESOLUTIONWIDTH / 2) - 200, (RESOLUTIONHEIGHT / 2) - 150);
		playerMoneyText.str("");
		myFont->Draw(rollText.str(), (RESOLUTIONWIDTH / 2) - 200, (RESOLUTIONHEIGHT / 2) - 100);
		rollText.str("");
		myFont->Draw(landsOnText.str(), (RESOLUTIONWIDTH / 2) - 200, (RESOLUTIONHEIGHT / 2) - 50);
		landsOnText.str("");
		myFont->Draw(tileEffectText.str(), (RESOLUTIONWIDTH / 2) - 200, (RESOLUTIONHEIGHT / 2));
		tileEffectText.str("");
		myFont->Draw(passedGoText.str(), (RESOLUTIONWIDTH / 2) - 200, (RESOLUTIONHEIGHT / 2) + 50);
		passedGoText.str("");

		// move the models on the board to the new tile
		dogModel->SetPosition(spriteXPosition[game.dog.mCurrentSquareValue], playerYPosition, spriteZPosition[game.dog.mCurrentSquareValue]);
		carModel->SetPosition(spriteXPosition[game.car.mCurrentSquareValue], playerYPosition, spriteZPosition[game.car.mCurrentSquareValue]);
		// adjust if visiting jail

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
