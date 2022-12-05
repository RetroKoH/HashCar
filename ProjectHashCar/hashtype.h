#ifndef HASHTYPE_H
#define HASHTYPE_H

// Based on Integer HashType class by:
// Author: Ivan Temesvari
// Date 4/10/2019
// Modified/Reworked by: Christopher Gaudet
// Date 12/3/2022

#include <iostream>
#include <string>
using namespace std;
const int MAX_ITEMS = 23;

class HashType
{
public:
	// Constructor
	HashType();
	
	// Member Functions
	void MakeEmpty();
	bool IsFull() const;
	int GetNumItems() const;
	void RetrieveItem(int, CarType&, bool&);	// Changed to object
	void InsertItem(CarType);					// Changed to object
	void DeleteItem(CarType);					// Changed to object
	int Hash(int, bool) const;					// Hash CarType using ID (Currently int)
	unsigned long int GetCollisions() const;
	// Overloaded Operator
	friend ostream& operator<<(ostream&, const HashType&);

private:
	int numItems;
	int size;
	CarType* info;
	unsigned long int numCollisions;
};
#endif

HashType::HashType()
{
	numCollisions = 0;
	numItems = 0;
	size = MAX_ITEMS;
	info = new CarType[size];	// Constructed w/ ID of -1 ("Empty")
}

bool HashType::IsFull() const
{
	return (numItems == size);
}

int HashType::GetNumItems() const
{
	return numItems;
}

// Updated to work with objects
void HashType::MakeEmpty()
// Post: list is empty.
{
	numItems = 0;
	delete[] info;
	info = new CarType[size];	// Constructed w/ ID of -1 ("Empty")
	numCollisions = 0;			// Reset collision count
}

// Updated to work with objects
void HashType::DeleteItem(CarType item)
{
	int location = 0;
	int startLoc = Hash(item.GetID(), false);
	int offset = Hash(item.GetID(), true);
	location = startLoc;

	do
	{
		if (info[location] == item || info[location] == -1) {
			info[location].Clear();		// Remove data of the given car
			numItems--;
			return;
		}
		else
			location = (location + offset) % size;	// Double hashing
	} while (location != startLoc);

	if (location == startLoc) {
		cout << "Item to delete not found." << endl;
	}
}

// Updated to employ double hashing
int HashType::Hash(int item, bool second) const
// Post: Returns an integer between 0 and hash table size.
{
	if (!second)
		return abs(item % size);
	else {
		return abs(13 - (item % 13));
	}
}

unsigned long int HashType::GetCollisions() const {
	return numCollisions;
}

// Updated to work with objects; Uses double-hashing
// Actual implementation will depend on whether ID is a string, or int.
void HashType::InsertItem(CarType item)
// Post: item is stored in the array at position item.Hash()
//       or the next free spot.
{
	/*int location = Hash(item.GetID(), false);

	while (!(info[location] == -1)) {
		location = (location + 1) % size;	// linear probing
		numCollisions++;
	}

	info[location] = item;
	numItems++;
	cout << "Car #" << numItems << " added w/ " << numCollisions << "Collisions" << endl;*/

	int hVal1 = Hash(item.GetID(), false), hVal2 = Hash(item.GetID(), true);
	int location = hVal1;
	int i = 1;
	cout << "Hashvals: " << hVal1 << " | " << hVal2 << "." << endl;

	while (!(info[location] == -1)) {
		location = (hVal1 + i * hVal2) % size;	// double hashing
		numCollisions++;
		i++;
	}

	info[location] = item;
	numItems++;
	cout << "Car #" << numItems << " added w/ " << numCollisions << "Collisions" << endl;
}

// Updated to work with objects
void HashType::RetrieveItem(int ID, CarType& item, bool& found)
{
	bool moreToSearch = true;
	int startLoc = Hash(ID, false);
	int offset = Hash(ID, true);
	int location = startLoc;

	// Search for the requested ID#
	do
	{
		if (info[location] == ID || info[location] == -1)
			moreToSearch = false;
		else
			location = (location + offset) % size;		// Double Hashing
	} while (location != startLoc && moreToSearch);

	found = (info[location] == ID);			// Set/Clear found flag accordingly

	if (found)
		item = info[location];				// Return the CarType if found
}

// Modified to display empty slots in the hash table appropriately
ostream& operator<<(ostream& out, const HashType& items) {
	out << "[ ";
	for (int i = 0; i < items.size; i++) {
		if (items.info[i] == -1) {
			if (i == 0)
				out << "EMPTY SLOT\n";
			else
				out << "-----\n" << "EMPTY SLOT\n";
		}
		else {
			if (i == 0)
				out << items.info[i];
			else
				out << "-----\n" << items.info[i];
		}
	}
	out << " ]" << endl;
	return out;
}
