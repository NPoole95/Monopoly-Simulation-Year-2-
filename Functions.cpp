#pragma once
#include "Functions.h"
#include "Definitions.h"
#include <ctime>


// function for seeding the random function
void ReadSeed()
{
	int temp; // temporary integer variable that is not kept
	ifstream fileInput; // ifstream for opening a file
	fileInput.open(SEEDFILENAME); // opens the input file

	if (fileInput.is_open()) // Checks to see that the file has been opened sucessfully
	{
		fileInput >> temp; // calls the file input and places the integer from the file into the temp int
		srand(temp); // calls the srand function using the seed that was read in
	}
}

// Returns a random number in the range 1 .. 6
// Note that I am using casting to convert one data type to another
int Random()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}

int NextInArray(int i, int arraySize) // Function to select the next point in a array (or cycle through if it reaches the end)
{
	int lastPoint = i; // number in the array for current point (one reached)
	int nextPoint;  // number in the array for the next point

	nextPoint = (lastPoint + ONE) % arraySize;  // cycles to the next member of the array using modulus (remainder)  e.g. 0>1>2>3>4>0>1>2

	return nextPoint; // returns the next position on the array / vector
}