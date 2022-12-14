// ProjectHashCar.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>     // cout
#include <stdlib.h>		// srand
#include <time.h>		// time
#include <chrono>
#include "cartype.h"
#include "hashtype.h"

typedef CarType ItemType;
using namespace std;

enum OptionType {ADD, RETRIEVE, DELETE, RESET, QUIT};

void randInitCar(CarType&);
void addNewCar(HashType&);

int main()
{
	//srand(time(NULL));							// Comment this out to utilize the same seed

	chrono::time_point<chrono::system_clock> start;
	chrono::time_point<chrono::system_clock> end;

	CarType* cars = new CarType[MAX_CARS];			// Initialize 20 cars to be processed
	cout << "We have " << MAX_CARS << " cars: " << endl;
	HashType myHashTable;							// Init hash table
	
	start = chrono::system_clock::now();			// Record start time
	// Randomly generate cars and hash them.
	for (int i = 0; i < MAX_CARS; i++) {
		randInitCar(cars[i]);				// Randomize car
		//cout << cars[i] << endl;			// Print attributes (Debug text)
		myHashTable.InsertItem(cars[i]);	// Insert into Hash Table (based on ID)
	}
	end = chrono::system_clock::now();				// Record end time
	chrono::duration<float> elapsed = end - start;	// Calculate and report time

	cout << myHashTable << "# of collisions: " << myHashTable.GetCollisions() << endl;
	cout << "Time elapsed: " << elapsed.count() << " seconds." << endl;


	// Gives users a chance to try out the other features of the HashType class
	int option, reqID;
	bool running = true, foundCar = false;
	CarType editCar;
	while (running) {
		cout << "Choose an option\n" <<
			"0. ADD CAR RECORD\n" <<
			"1. FIND CAR RECORD\n" << 
			"2. DELETE CAR RECORD\n" << 
			"3. RESET HASH TABLE\n" << 
			"4. EXIT PROGRAM\n";
		cin >> option;
		try {
			if (cin.fail()) {
				throw "ERROR - Non-Integer Menu Input";
			}
		}
		catch (const char* error) {
			cout << error << endl;	// Print error message
			cin.clear();			// Clear cin flag
			cin.ignore();			// Ignore so we don't softlock
		}

		switch (OptionType(option)) {
		case ADD:
			{
				if (!myHashTable.IsFull()) {
					cout << "Adding new car record:" << endl;
					addNewCar(myHashTable);
				}
				else
					cout << "Cannot add cars. Delete records first." << endl;
			}
			break;
		case RETRIEVE:
			{
				while (!foundCar) {
					cout << "Give ID of car record to retrieve: " << endl;
					cin >> reqID;
					myHashTable.RetrieveItem(reqID, editCar, foundCar);

					if (!foundCar) {
						char yes = ' ';
						cout << "Car not found. 'Y' to search again.";
						cin >> yes;
						if (yes != 'Y' && yes != 'y')
							break;
					}
					else {
						cout << "Car has been found!\n" << editCar << endl;
					}
				} foundCar = false; // Reset flag for next use.
			}
			break;
		case DELETE:
			{
				if (myHashTable.GetNumItems() > 0) {
					cout << "Give ID of car record to delete: " << endl;
					cin >> reqID;
					myHashTable.RetrieveItem(reqID, editCar, foundCar);
					if (!foundCar)
						cout << "Car record not found!" << endl;
					else {
						char yes = ' ';
						cout << "'Y' to delete this car:\n" << editCar << endl;
						cin >> yes;
						if (yes == 'Y' || yes == 'y') {
							myHashTable.DeleteItem(editCar);
							cout << "Car #" << reqID << " has been deleted!" << endl;
						}
					}
					foundCar = false; // Reset flag for next use.
				}
				else
					cout << "Cannot delete from an empty table." << endl;
			}
			break;
		case RESET:
			{
				cout << "Resetting hash table:" << endl;
				myHashTable.MakeEmpty();
				delete[] cars;
				cars = new CarType[MAX_CARS];			// Initialize 20 cars to be processed
				cout << "Generating " << MAX_CARS << " new cars: " << endl;
				start = chrono::system_clock::now();	// Record start time
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
			}
			break;
		case QUIT:
			running = false;
			break;
		default:
			cout << "ERROR - Invalid Menu Integer" << endl;
			break;
		}
	}
	return 0;
}

void randInitCar(CarType& car) {
	// Function: Sets car's members to randomized values.
	// Pre:	 The object has already been initialized.
	// Post: The object now has fully randomized member values.

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

void addNewCar(HashType& table) {
	// Function: Create a new car and adds it to HashType table.
	// Pre:	 Given HashType table has been initialized.
	// Post: Object is created and hashed into the table.

	int year = 0, miles = -1;
	string color = "", make, model;
	ColorType newColor = BLACK;

	while (year == 0) {
		cout << "Enter year of car (1960-2022): " << endl;
		cin >> year;

		try {
			if (cin.fail()) {
				throw "ERROR - Non-Integer Year Input";
			}
		}
		catch (const char* error) {
			cout << error << endl;	// Print error message
			year = 0;				// Not sure if necessary??
			cin.clear();			// Clear cin flag
			cin.ignore();			// Ignore so we don't softlock
		}

		if ((1960 > year || year > 2022)) {
			cout << "Invalid year" << endl;
			year = 0;
			cin.clear();
			cin.ignore();
		}
	}

	while (miles == -1) {
		cout << "Enter mileage: " << endl;
		cin >> miles;

		try {
			if (cin.fail()) {
				throw "ERROR - Non-Integer mileage Input";
			}
		}
		catch (const char* error) {
			cout << error << endl;	// Print error message
			miles = -1;				// Not sure if necessary??
			cin.clear();			// Clear cin flag
			cin.ignore();			// Ignore so we don't softlock
		}

		if (miles < 0) {
			cout << "Invalid mileage" << endl;
			miles = -1;
			cin.clear();
			cin.ignore();
		}
	}
	
	while (color == "") {
		cout << "Enter color: \n" <<
			"(White, Black, Gray, Red, Green, Blue, Gold, Silver, Brown)" << endl;
		cin >> color;

		for (int i = 0; i < 10; i++)
		{
			if (color == colors[i]) {
				newColor = ColorType(i);
				break;
			}
			else if (i == 9)
				color = "";
		}
		if (color == "")
			cout << "Color not found. Try again." << endl;
	}
	
	cout << "Enter make: " << endl;
	cin >> make;
	
	cout << "Enter model: " << endl;
	cin >> model;

	CarType newCar(year, miles, make, model, newColor, rand() % 999999);
	table.InsertItem(newCar);	// Insert into Hash Table (based on ID)
	cout << "\nCar #" << table.GetNumItems() << " added!" << endl <<
		newCar << endl;
}
