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

	// Methods
	void MakeEmpty();										// Function: Returns the table to the empty state
	bool IsFull() const;									// Function: Determines whether table is full
	int GetNumItems() const;								// Function: Determines the number of elements in table
	void RetrieveItem(int, CarType&, bool&);				// Function: Retrieves object whose key matches given ID
	void InsertItem(CarType);								// Function: Adds item to table
	void DeleteItem(CarType);								// Function: Deletes item from table
	int Hash(int, bool) const;								// Function: Hash CarType using class member ID
	unsigned long int GetCollisions() const;				// Function: Returns number of hashing collisions
	friend ostream& operator<<(ostream&, const HashType&);	// Function: Outputs table to console

private:
	// Members
	int numItems;						// The number of elements in the hash table
	int size;							// The size of the table
	CarType* info;						// Pointer to the elements in the table
	unsigned long int numCollisions;	// The number of hashing collisions
};
#endif

HashType::HashType() {
	// Default Constructor

	numCollisions = 0;
	numItems = 0;				// Table is empty
	size = MAX_ITEMS;			// Table size capped at a prime number
	info = new CarType[size];	// Constructed w/ ID of -1 ("Empty")
}

void HashType::MakeEmpty() {
	// Function: Returns the table to the empty state.
	// Pre:		 Table has been initialized.
	// Post:	 Table is empty.

	numItems = 0;
	delete[] info;
	info = new CarType[size];	// Constructed w/ ID of -1 ("Empty")
	numCollisions = 0;			// Reset collision count
}

bool HashType::IsFull() const {
	// Function: Determines whether table is full.
	// Pre:		 Hash table has been initialized.
	// Post:	 Function value = (table is full)

	return (numItems == size);
}

int HashType::GetNumItems() const {
	// Function: Determines the number of elements in hash table.
	// Pre:		 Hash table has been initialized.
	// Post:	 Function value = number of elements in table

	return numItems;
}

void HashType::RetrieveItem(int ID, CarType& item, bool& found) {
	// Function: Retrieves CarType object whose key matches ID (if
	//           present).
	// Pre:  Hash table has been initialized.
	//       Key member of item is initialized.
	// Post: If there is an element item whose ID value matches
	//       the given ID, then found = true and item contains
	//       the contents of the CarType object if it is found.
	// 	     otherwise, found = false and item is returned unchanged.
	//       Table is unchanged.

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

void HashType::InsertItem(CarType item) {
	// Function: Adds item to table
	// Pre:	 Table has been initialized. Table is not full.
	//		 Item is not in table.
	// Post: Item is stored in the array at position item.Hash()
	//		 or the next free spot.
	// NOTE: Debug text commented out

	int startLoc = Hash(item.GetID(), false);
	int offset = Hash(item.GetID(), true);
	int location = startLoc;
	//cout << "Hashvals: " << startLoc << " | " << offset << "." << endl;

	while (!(info[location] == -1)) {
		location = (location + offset) % size;	// double hashing
		numCollisions++;
	}

	info[location] = item;
	numItems++;
	//cout << "Car #" << numItems << " added w/ " << numCollisions << "Collisions" << endl;
}

void HashType::DeleteItem(CarType item) {
	// Function: Deletes item from hash table.
	// Pre:	 Hash table has been initialized.
	// Post: Table element is deleted.

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

int HashType::Hash(int item, bool second) const {
	// Function: Hash CarType using class member ID.
	//			 If second is true, a secondary hash value is used.
	//			 Otherwise, the standard division method will be used.
	// Pre:  Table has been initialized.
	// Post: Returns one of two integers based on ID.

	if (!second)
		return abs(item % size);	  // Returns an int between 0 and table size
	else
		return abs(13 - (item % 13)); // Returns a non-zero int from 1 to 13
}

unsigned long int HashType::GetCollisions() const {
	// Function: Returns number of collisions that occured during building of the hash table
	// Pre:  Table has been built.
	// Post: Returns number of collisions.

	return numCollisions;
}

ostream& operator<<(ostream& out, const HashType& items) {
	// Modified to display empty slots in the hash table appropriately
	out << "[ ";

	for (int i = 0; i < items.size; i++) {

		// If there is no car stored in this slot
		if (items.info[i] == -1) {
			if (i == 0)
				out << "EMPTY SLOT\n";
			else
				out << "-----\n" << "EMPTY SLOT\n";
		}

		// If there is a car in this slot
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
