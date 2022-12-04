#ifndef HASHTYPE_H
#define HASHTYPE_H

// Author: Ivan Temesvari
// Date 4/10/2019

#include <iostream>
#include <string>
using namespace std;
const int MAX_ITEMS = 20;

class HashType
{
public:
	// Constructor
	HashType();
	
	// Member Functions
	void MakeEmpty();
	bool IsFull() const;
	int GetNumItems() const;
	void RetrieveItem(CarType&, bool&);			// Changed to object
	void InsertItem(CarType);					// Changed to object
	void DeleteItem(CarType);					// Changed to object
	int Hash(int) const;						// Hash CarType using ID (Currently int)
	unsigned long int GetCollisions() const;
	// Overloaded Operator
	friend ostream& operator<<(ostream&, const HashType&);

private:
	int a; // the value used for a polynomial hash function (Only used if we utilize strings for ID)
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

}

// Updated to work with objects
void HashType::DeleteItem(CarType item)
{
	int location = 0;
	int startLoc = Hash(item.GetID());
	location = startLoc;

	do
	{
		if (info[location] == item || info[location] == -1) {
			info[location].Clear();		// Remove data of the given car
			numItems--;
			return;
		}
		else
			location = (location + 1) % size;
	} while (location != startLoc);

	if (location == startLoc) {
		cout << "Item to delete not found." << endl;
	}
}

int HashType::Hash(int item) const
// Post: Returns an integer between 0 and hash table size.
{
	return abs(item % size);
}

unsigned long int HashType::GetCollisions() const {
	return numCollisions;
}

// Updated to work with objects
// Actual implementation will depend on whether ID is a string, or int.
void HashType::InsertItem(CarType item)
// Post: item is stored in the array at position item.Hash()
//       or the next free spot.
{
	int location = Hash(item.GetID());

	while (!(info[location] == -1)) {
		location = (location + 1) % size;	// linear probing (Change method)
		numCollisions++;
	}

	info[location] = item;					// Ensure that object assignment works correctly.
	numItems++;
}

// Updated to work with objects
void HashType::RetrieveItem(CarType& item, bool& found)
{
	bool moreToSearch = true;
	int startLoc = Hash(item.GetID());
	int location = startLoc;

	do
	{
		if (info[location] == item || info[location] == -1)
			moreToSearch = false;
		else
			location = (location + 1) % size;
	} while (location != startLoc && moreToSearch);

	found = (info[location] == item);

	if (found)
		item = info[location];					// Ensure that object assignment works correctly.
}

ostream& operator<<(ostream& out, const HashType& items) {
	out << "[ ";
	for (int i = 0; i < items.size; i++) {
		if (i == 0)
			out << items.info[i];
		else
			out << "-----\n" << items.info[i];
	}
	out << " ]" << endl;
	return out;
}
