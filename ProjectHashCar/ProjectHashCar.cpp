// ProjectHashCar.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>     // cout
#include <stdlib.h>		// srand
#include <time.h>		// time
#include <chrono>
#include "cartype.h"
#include "hashtype.h"

typedef CarType ItemType;
using namespace std;

// We need to use this function to randomize the car, as the default
// constructor needs to be used for the "empty" spaces in the hash table.
void randInitCar(CarType&);

int main()
{
	//srand(time(NULL));							// Comment this out to utilize the same seed

	chrono::time_point<chrono::system_clock> start;
	chrono::time_point<chrono::system_clock> end;

	CarType cars[MAX_CARS];							// Initialize 20 cars to be processed
	cout << "We have " << MAX_CARS << " cars: " << endl;
	HashType myHashTable;							// Init hash table
	
	start = chrono::system_clock::now();			// Record start time
	// Randomly generate cars and hash them.
	for (int i = 0; i < MAX_CARS; i++) {
		randInitCar(cars[i]);				// Randomize car
		//cout << cars[i] << endl;			// Print attributes
		myHashTable.InsertItem(cars[i]);	// Insert into Hash Table (based on ID)
	}
	end = chrono::system_clock::now();				// Record end time
	chrono::duration<float> elapsed = end - start;	// Calculate and report time

	cout << myHashTable << "# of collisions: " << myHashTable.GetCollisions() << endl;
	cout << "Time elapsed: " << elapsed.count() << " seconds." << endl;
	return 0;
}

void randInitCar(CarType& car) {
	int year = 1990 + (rand() % 32);
	car.SetYear(year);							// Year is random from 1990 to 2022

	int age = 2022 - year;
	int miles = 0;								// Randomly generated; 10-12k miles per year
	for (int i = 0; i < age; i++)
		miles += 10000 + (rand() % 2000);
	car.SetMileage(miles);

	// Use enum/int to pull the correct string.
	MakeType getMake = MakeType(rand() % 6);
	car.SetMake(makes[getMake]);				// Get random make.
	car.SetModel(models[getMake][rand() % 5]);	// Then pull a model name based on make.
	car.SetColor(ColorType(rand() % 9));		// Assign a random color

	car.SetID(rand() % 999999);					// Assign a random 6 digit ID number
	// ID will later be its own IDType class, consisting of either an int, or string.
}


// In case you are using Visual Studio: (Otherwise, ignore this)
// 
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
// 
// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
