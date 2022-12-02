// ProjectHashCar.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>     // cout
#include <stdlib.h>		// srand
#include <time.h>		// time
#include "hashtype.h"
#include "cartype.h"

typedef CarType ItemType;
using namespace std;

int main()
{
	srand(time(NULL));
	CarType cars[MAX_ITEMS];		// Randomly initialize 20 cars to be processed
	cout << "We have 20 cars: " << endl;
	
	HashType myHashTable;
	
	// Instead of randomly setting values in this for loop, I instead had the CarType
	// constructor randomly initialize values when generated.
	for (int i = 0; i < MAX_ITEMS; i++) {
		cout << cars[i] << endl;
		myHashTable.InsertItem(cars[i].GetID());
	}

	// For now, we are only hasing integers. We are not yet hasing the actual objects
	cout << myHashTable << "# of collisions: " << myHashTable.GetCollisions() << endl;
	return 0;
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
